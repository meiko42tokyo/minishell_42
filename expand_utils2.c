#include "shell.h"

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
	free(head);
	return (tmp1);
}

void	find_min_dis(int *dis, char **word)
{
	char	*ops;
	int		i;

	*dis = ft_strlen(*word + 1);
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

char	*get_exit_status(void)
{
	return (ft_itoa(g_shell->status));
}
