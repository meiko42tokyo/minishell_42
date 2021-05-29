#include "shell.h"

// TODO: If in the quote, don't quote until the quote ends
char	**get_argv(char *input)
{
	char	**argv;
	char	*separator;

	separator = " ";
	argv = ft_split((const char*)input, *separator);
	if (argv == NULL)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	return (argv);
}

char	*ft_min_strchr(char *input)
{
	size_t	min_dis;
	size_t	tmp;
	char 	ops[] = {
		'|', ';', '<', '>', 0
	};
	int	index;

	index = 0;
	min_dis = ft_strchr(input, 0) - input;
	if (ft_strnstr(input, ">>", 2) != NULL)
	{
		tmp = ft_strchr(input, ops[index]) - input;
		if (min_dis > tmp)
			min_dis = tmp;
	}
	while (ops[index])
	{
		if (ft_strchr(input, ops[index]) != NULL)
			tmp = ft_strchr(input, ops[index]) - input;
		if (min_dis > tmp)
			min_dis = tmp;
		index++;
	}
	if (ft_strlen(input) == min_dis)
		min_dis = 0;
	return (input + min_dis);;
}

int	get_op(char op)
{
	if (op == '|')
		return (OP_PIPE);
	if (op == ';')
		return (OP_SEP);
	return (OP_OTHER);
}

t_cmd	*make_cmdlist(char *input)
{
	t_cmd	*head;
	t_cmd	*cmd;
	char	*word;
	char	*new_pos;

	head = NULL;
	new_pos = NULL;
	if (input == NULL)
		return (NULL);
	while ((new_pos = ft_min_strchr(input)) > input)
	{
		word = ft_strndup(input, new_pos - input);
		// if redirect, check >>. and record somehow?
		cmd = ft_cmdnew(get_argv(word), get_op(*new_pos));
		free(word);
		input = new_pos;
		input++;
		ft_cmdadd_back(&head, cmd);
	}
	word = ft_strndup(input, ft_strlen(input));
	cmd = ft_cmdnew(get_argv(word), 0);
	ft_cmdadd_back(&head, cmd);	
	return (head);
}
