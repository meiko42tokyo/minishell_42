#include "shell.h"

// record until control as word and also record control. If in the quote, record until the quote end

// <argv> split by the space. 
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

// compare every strchr
// return minimum number of distance
// use the number for substr
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
	while (ops[index])
	{
		if (ft_strchr(input, ops[index]) == NULL)
		{
			index++;
			continue ;
		}
		tmp = ft_strchr(input, ops[index]) - input;
		if (min_dis > tmp)
			min_dis = tmp;
		index++;
	}
	if (ft_strlen(input) == min_dis)
		min_dis = 0;
	return (input + min_dis);;
}


// transform input->t_cmd
t_cmd	*make_cmdlist(char *input)
{
	t_cmd	*head;
	t_cmd	*cmd;
	char	*word;
	char	*new_pos;

	head = NULL;
	new_pos = NULL;
	while ((new_pos = ft_min_strchr(input)) > input)
	{
		word = ft_strndup(input, new_pos - input);
		// if redirect, check >>. and record somehow?
		cmd = ft_cmdnew(get_argv(word), *new_pos);
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
