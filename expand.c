#include "shell.h"

void	strshift(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	ft_memmove(word, word + 1, len - 1);
	word[len - 1] = '\0';
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

void	check_word(char *word, t_env *env)
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
			printf("test\n");
			*word = *(word + 1);
			word++;
			strshift(word);
		}
		else if (*word == '$' && state != SINGLE_Q)
		{
			//check env val exist
			//
			if (env)
				printf("env\n");
			word++;
		}
		else
		{
			if (*word == '\0')
				break;
			word++;
		}
	}
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
			check_word(node->argv[arg_i], env);
			arg_i++;
		}
		if (node->next == NULL)
			break ;
		node = node->next;
	}	
}
