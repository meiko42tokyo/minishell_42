#include "shell.h"

char	**get_argv(char *input)
{
	char	**argv;
	char	*separator;

	separator = " ";
	argv = ft_split((const char *)input, *separator);
	if (argv == NULL)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	return (argv);
}

void	get_token(char *new_pos, int *token)
{
	if (*new_pos == ';')
		*token = OP_SEP;
	else if (*new_pos == '|')
		*token = OP_PIPE;
	else if (*new_pos == '<')
	{
		if (*(new_pos + 1) == '<')
			*token = RD_INSERT;
		else
			*token = RD_LESSER;
	}
	else if (*new_pos == '>')
	{
		if (*(new_pos + 1) == '>')
			*token = RD_EXTRACT;
		else
			*token = RD_GREATER;
	}
	else if (*new_pos == '\"')
		*token = BR_DOUBLE;
	else if (*new_pos == '\'')
		*token = BR_SINGLE;
	else
		*token = OTHER;
}

size_t	op_size(int index)
{
	if (index == RD_EXTRACT || index == RD_INSERT)
		return (2);
	else
		return (1);
}

char	*ft_min_strchr(char *input, int *token)
{
	size_t	min_dis;
	size_t	tmp;
	char	**ops;
	int		index;

	index = 0;
	ops = set_ops();
	min_dis = ft_strchr(input, 0) - input;
	while (ops[index])
	{
		if (ft_strnstr(input, ops[index], ft_strlen(input)) != NULL)
		{
			tmp = ft_strnstr(input, ops[index], ft_strlen(input)) - input;
			if (min_dis > tmp)
				min_dis = tmp;
		}
		index++;
	}
	free(ops);
	get_token(input + min_dis, token);
	return (input + min_dis);
}

size_t	ft_strplen(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
