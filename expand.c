#include "shell.h"

void	strshift(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	printf("word:%s, len:%zu\n", word, len);
	ft_memmove(word, word + 1, len - 1);
	word[len - 1] = '\0';
}

void	ft_mempshift(char **dst, char **src, size_t len)
{
	while (len--)
		*dst++ = *src++;
}

void	strpshift(char **argv, int arg_i)
{
	size_t	len;
	char	*cur_arg;
	int	cur_i;

	len = 0;
	cur_arg = argv[arg_i];
	cur_i = arg_i;
	while(argv[arg_i++])
		len++;
	free(cur_arg);
	ft_mempshift(argv + cur_i , argv + cur_i + 1, len - 1);
	argv[cur_i + len - 1] = NULL;
} 

int	strnshift(char *word, int dis, char *head)
{
	size_t	len;

	len = ft_strlen(word + 1);
	ft_memmove(word, word + dis + 1, len - dis);
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

char	*set_env_ops(void)
{
	char	*ops;

	ops = (char *)malloc(sizeof (char) * ENV_OPS_SIZE + 1);
	ops[0] = '$';
	ops[1] = '\"';
	ops[2] = '\'';
	ops[ENV_OPS_SIZE] = '\0';
	return (ops);
}

char	*set_new_arg(char *head, int cur_pos, char *env_val, char *left_word)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strndup(head, cur_pos);
	cur_pos += ft_strlen(env_val);
	tmp2 = ft_strjoin(tmp1, env_val);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, left_word + 1);
	free(tmp2);
	tmp1[ft_strlen(tmp1)] = '\0';
	return (tmp1);
}

void	find_min_dis(int *dis, char **word)
{
	char	*ops;
	int	i;

	ops = set_env_ops();
	i = 0;
	while (ops[i])
	{
		if (ft_strchr(*word + 1, ops[i]))
		{
			if (ft_strchr(*word + 1, ops[i]) - *word - 1 < *dis)
				*dis = ft_strchr(*word + 1, ops[i]) - *word - 1;
		}
		i++;
	}
	free(ops);
}

// 終了ステータスを取得する
char	*get_exit_status()
{
	return (ft_itoa(status));
}

int	expand_env(char **word, t_env *env, t_cmd *node, int arg_i)
{
	int	dis;
	int	env_hit;
	int	cur_pos;
	char	*exit_status;

	env_hit = 0;
	cur_pos = *word - node->argv[arg_i];
	if (*(*word + 1) == '?')
	{
		exit_status = get_exit_status();
		node->argv[arg_i] = set_new_arg(node->argv[arg_i], cur_pos, exit_status, *word + 2);
		free(exit_status);
		*word += 2;
		return (0);
	}
	dis = ft_strlen(*word + 1);
	find_min_dis(&dis, word);
	while (env)
	{
		if (ft_strncmp(*word + 1, env->name, dis) == 0)
		{
			node->argv[arg_i] = set_new_arg(node->argv[arg_i], cur_pos, env->value, *word + dis);
			env_hit = 1;
		}
		env = env->next;	
	}
	if (env_hit == 0)
	{
		if (strnshift(*word, dis, node->argv[arg_i]))
			return (1);
	}
	*word = node->argv[arg_i];
	(*word)[ft_strlen(*word)] = '\0';
	*word += cur_pos;
	return (0);
}

int	check_word(char *word, t_env *env, t_cmd *node, int arg_i)
{
	int	state;

	state = NOT_Q;
	while (*word)
	{
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
			if (expand_env(&word, env, node, arg_i))
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
		arg_i = 0;
		while (node->argv[arg_i])
		{
			if (check_word(node->argv[arg_i], env, node, arg_i))
				strpshift(node->argv, arg_i);
			arg_i++;
		}
		if (node->next == NULL)
			break ;
		node = node->next;
	}	
}
