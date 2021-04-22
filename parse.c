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
size_t	ft_min_strchr(char *input)
{
	size_t	min_dis;
	size_t	tmp;
	char 	ops[] = {
		'|', ';', '<', '>', 0
	};
	int	index;

	index = 0;
	printf("func ft_min_strchr:input - input_end: %ld\n", ft_strchr(input, 0) - input);
	min_dis = ft_strchr(input, 0) - input;
	printf("min_dis: %zu\n", min_dis);
	while (ops[index])
	{
		printf("func min_strchr: ft_strchr%s\n", ft_strchr(input, ops[index]));
		printf("func min_strchr: ops[index]%c\n", ops[index]);
		if (ft_strchr(input, ops[index]) == NULL)
{
	index++;
	continue ;
}
		tmp = ft_strchr(input, ops[index]) - input;	
		printf("func min_strchr: tmp:%zu\n", tmp);
		printf("func min_strchr: cand of mindis->%c\n", input[tmp]);
		if (min_dis > tmp)
			min_dis = tmp;
		printf("current min :%c, %zu\n", input[min_dis], min_dis);	
		index++;
	}
	if (ft_strlen(input) == min_dis)
		return (0);
	return (min_dis);
}


// transform input->t_cmd
t_cmd	*make_cmdlist(char *input)
{
	t_cmd	*head;
	size_t	dis;
	//size_t	pipe_dis;

	head = NULL;
	//pipe_dis = ft_strchr(input, '|') - input;
	//printf("pipe_dis : %zu\n", pipe_dis);
	// split input by certain char
	while ((dis = ft_min_strchr(input) > 0))
	{
		printf("dis:%zu\n", dis);
		//save before certain word
		input += dis;
	}
	// input->argv
	// input->op
	// call ft_cmdnew()
	return (head);
}
