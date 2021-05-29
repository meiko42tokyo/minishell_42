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

void	get_token(char *new_pos, int *token)
{
	if (*new_pos == ';')
		*token = OP_SEP;
	if (*new_pos == '|')
		*token = OP_PIPE;
	else
		*token = OTHER;
}

char	**set_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof (char *) * OPS_SIZE);
	ops[OP_SEP] = ";";
	ops[OP_PIPE] = "|";
	ops[RD_LESSER] = "<";
	ops[RD_GREATER] = ">";
	ops[RD_EXTRACT] = ">>";
	ops[OPS_SIZE - 1] = 0;
	return (ops);
}

char	*ft_min_strchr(char *input, int *token)
{
	size_t	min_dis;
	size_t	tmp;
	char 	**ops; 
	int	index;

	index = 0;
	ops = set_ops();
	min_dis = ft_strchr(input, 0) - input;
	if (ft_strnstr(input, ">>", 2) != NULL)
	{
		tmp = ft_strnstr(input, ">>", 2) - input;
		if (min_dis > tmp)
		{
			min_dis = tmp;
			*token = RD_EXTRACT;
		}
	}
	while (ops[index])
	{
		if (ft_strchr(input, *ops[index]) != NULL)
		{
			tmp = ft_strchr(input, *ops[index]) - input;
			if (min_dis > tmp)
				min_dis = tmp;
		}
		index++;
	}
	if (ft_strlen(input) == min_dis)
		min_dis = 0;
	if (min_dis)
		get_token(input + min_dis, token);
	free(ops);
	return (input + min_dis);;
}

int	get_op(char op)
{
	if (op == '|')
		return (OP_PIPE);
	if (op == ';')
		return (OP_SEP);
	return (OTHER);
}

int	is_op(int *token)
{
	if (*token == OP_PIPE || *token == OP_SEP)
		return (1);
	else
		return (0);
}

int	is_two_char(int *token)
{
	if (*token == RD_EXTRACT)
		return (1);
	else
		return (0);
}

t_cmd	*make_cmdlist(char *input)
{
	t_cmd	*head;
	t_cmd	*cmd;
	char	*word;
	char	*new_pos;
	int	token;

	head = NULL;
	new_pos = NULL;
	if (input == NULL)
		return (NULL);
	token = OTHER;
	while ((new_pos = ft_min_strchr(input, &token)) > input)
	{
		word = ft_strndup(input, new_pos - input);
		if (is_op(&token))
		{
			cmd = ft_cmdnew(get_argv(word), get_op(*new_pos));
			ft_cmdadd_back(&head, cmd);
		}
		else
		{
			//append_arg(word);
		}
		free(word);
		input = new_pos;
		if (is_two_char(&token))
			input += 2;
		else
			input++;
	}	
	word = ft_strndup(input, ft_strlen(input));
	cmd = ft_cmdnew(get_argv(word), OTHER);
	ft_cmdadd_back(&head, cmd);
	free(word);
	ft_print_cmdlist(&head);
	return (head);
}
