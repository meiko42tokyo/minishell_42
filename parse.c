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
	if (*new_pos == '<')
		*token = RD_LESSER;
	if (*new_pos == '>')
	{
		if (*(new_pos + 1) == '>')
			*token = RD_EXTRACT;
		else
			*token = RD_GREATER;
	}
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

int	get_op(char *op)
{
	if (ft_strncmp(op, ";", 1) == 0)
		return (OP_SEP);
	if (ft_strncmp(op, "|", 1) == 0)
		return (OP_PIPE);
	if (ft_strncmp(op, "<", 1) == 0)
		return (RD_LESSER);
	if (ft_strncmp(op, ">", 1) == 0)
		return (RD_GREATER);
	if (ft_strncmp(op, ">>", 2) == 0)
		return (RD_EXTRACT);
	return (OTHER);
}

int	is_op(int *token)
{
	if (*token == OP_PIPE || *token == OP_SEP)
		return (1);
	else
		return (0);
}

int	is_redirect(int token)
{
	if (token == RD_LESSER || token == RD_GREATER || token == RD_EXTRACT)
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

size_t	ft_strplen(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

char	*put_rd(int token)
{
	if (token == RD_LESSER)
		return ("<");
	if (token == RD_GREATER)
		return (">");
	if (token == RD_EXTRACT)
		return (">>");
	return (NULL);
}

char	**copy_argvs(char *argv[], char **old_argv, size_t len, int token)
{
	char	**new_argv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_argv = (char**)ft_calloc(len + 1 + 1, sizeof (char *));
	if (new_argv == NULL)
		return (NULL);
	while (old_argv[i])
	{
		new_argv[i] = ft_strdup(old_argv[i]);
		i++;
	}
	new_argv[i] = ft_strdup(put_rd(token));
	i++;
	while (argv[j])
	{
		new_argv[i] = ft_strdup(argv[j]);
		i++;
		j++;
	}
	new_argv[i] = NULL;
	return (new_argv);
}

int	append_arg(char *argv[], t_cmd **head)
{
	t_cmd	*node;
	size_t	old_len;
	size_t	new_len;
	char	**old_argv;

	node = *head;
	while (node)
	{
		if (node->next == NULL)
			break;
		node = node->next;
	}
	old_argv = node->argv;
	old_len = ft_strplen(node->argv);
	new_len = ft_strplen(argv);
	node->argv = copy_argvs(argv, old_argv, old_len + new_len, node->op);
	if (node->argv == NULL)
		return (1);
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
	cmd = NULL;
	new_pos = NULL;
	if (input == NULL)
		return (NULL);
	token = OTHER;
	while ((new_pos = ft_min_strchr(input, &token)) > input)
	{
		word = ft_strndup(input, new_pos - input);
		if (cmd && is_redirect(cmd->op))
		{
			if (append_arg(get_argv(word), &head) != 0)
				return (NULL);
			cmd->op = get_op(new_pos);
		}
		else
		{
			cmd = ft_cmdnew(get_argv(word), get_op(new_pos));
			ft_cmdadd_back(&head, cmd);
		}
		free(word);
		input = new_pos;
		if (is_two_char(&token))
			input += 2;
		else
			input++;
	}
	word = ft_strndup(input, ft_strlen(input));
	if (cmd && is_redirect(cmd->op))
	{
		if (is_redirect(cmd->op))
		{
			if (append_arg(get_argv(word), &head) != 0)
				return (NULL);
			cmd->op = get_op(new_pos);
		}
	}
	else
	{
		cmd = ft_cmdnew(get_argv(word), OTHER);
		ft_cmdadd_back(&head, cmd);
	}
	free(word);
	ft_print_cmdlist(&head);
	return (head);
}
