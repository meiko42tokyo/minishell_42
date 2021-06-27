#include "shell.h"

void	strshift(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	ft_memmove(word, word + 1, len - 1);
	word[len - 1] = '\0';
}

void	strpshift(char **argv, int arg_i)
{
	size_t len;
	char	*cur_arg;

	len = 0;
	cur_arg = argv[arg_i];
	while(argv[arg_i])
		len++;
	free(argv[arg_i]);
	ft_memmove(argv[arg_i], argv[arg_i + 1], len - 1);
	argv[arg_i + len] = NULL;
	
} 

int	strnshift(char *word, int dis, char *head)
{
	size_t	len;

	printf("strnshift\n");
	len = ft_strlen(word);
	ft_memmove(word, word + dis, len - dis);
	word[len - dis] = '\0';
	if (*head == '\0')
		return (1);
	return (0);
}

int	is_escape(char c)
{
	if (c == '\"' || c == '\"' || c == '`' || c == '$')
		return (1);
	else
		return (0);
}

void	br(int *state, char **word)
{
	if (**word == '\"')
	{
		if (*state == DOUBLE_Q)
			*state = NOT_Q;
		else if (*state == NOT_Q)
			*state = DOUBLE_Q;
		if (*state != SINGLE_Q)
			strshift(*word);
		else
			*word = *word + 1;
	}
	else if (**word == '\'')
	{
		if (*state == SINGLE_Q)
			*state = NOT_Q;
		else if (*state == NOT_Q)
			*state = SINGLE_Q;
		if (*state != DOUBLE_Q)
			strshift(*word);
		else
			*word = *word + 1;
	}
}

int	expand_env(char **word, t_env *env, char *head)
{
	int	dis;

	if (ft_strchr(*word + 1, '$'))
		dis = ft_strchr(*word + 1, '$') - *word;
	else
		dis = ft_strlen(*word + 1);
	printf("dis:%d\n", dis);
	while (env)
	{
		if (ft_strncmp(*word + 1, env->name, ft_strlen(env->name)) == 0)
		{
			printf("hit !\n");
			if (strnshift(*word, dis, head))
				return (1);
		}
		else
			printf("wrong env:%s, len:%zu, ft_strncmp():%d \n", env->name, ft_strlen(env->name), ft_strncmp(*word, env->name, ft_strlen(env->name)));
		env = env->next;	
	}
	*word += dis + 1;
	return (0);
}

int	check_word(char *word, t_env *env)
{
	int	state;
	char 	*head;

	head = word;
	state = NOT_Q;
	while (word)
	{
		printf("word:%s, state:%d\n", word, state);
		if (*word == '\'' || *word == '\"')
			br(&state, &word);
		else if (*word == '\\' && is_escape(*(word + 1)) && state == DOUBLE_Q)
		{
			*word = *(word + 1);
			word++;
			strshift(word);
		}
		else if (*word == '$' && state != SINGLE_Q)
		{
			if (expand_env(&word, env, head))
				return (1);
		}
		else
		{
			if (*word == '\0')
				break;
			word++;
		}
	}
	return (0);
}

void	expand(t_cmd **head, t_env *env)
{
	t_cmd	*node;
	int	arg_i;

	node = *head;
	arg_i = 0;
	while (node)
	{
		while (node->argv[arg_i])
		{
			if (check_word(node->argv[arg_i], env))
				strpshift(node->argv, arg_i);
			arg_i++;
		}
		if (node->next == NULL)
			break ;
		node = node->next;
	}	
}
