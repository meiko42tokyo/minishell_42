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
	else if (*new_pos == '|')
		*token = OP_PIPE;
	else if (*new_pos == '<')
		*token = RD_LESSER;
	else if (*new_pos == '>')
	{
		if (*(new_pos + 1) == '>')
			*token = RD_EXTRACT;
		else
			*token = RD_GREATER;
	}
	else if (*new_pos == '\"')
		*token = BR_DOUBLE;
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
	ops[BR_DOUBLE] = "\"";
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
	free(ops);
	get_token(input + min_dis, token);
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
	if (ft_strncmp(op, ">>", 2) == 0)
		return (RD_EXTRACT);
	if (ft_strncmp(op, ">", 1) == 0)
		return (RD_GREATER);
	if (ft_strncmp(op, "\"", 1) == 0)
		return (BR_DOUBLE);
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

char	*put_token(int token)
{
	if (token == OP_SEP)
		return (";");
	if (token == OP_PIPE)
		return ("|");
	if (token == RD_LESSER)
		return ("<");
	if (token == RD_GREATER)
		return (">");
	if (token == RD_EXTRACT)
		return (">>");
	if (token == BR_DOUBLE)
		return ("\"");
	return (NULL);
}

char	**copy_argvs(char *argv[], char **old_argv, size_t len, int token)
{
	char	**new_argv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_argv = (char**)ft_calloc(len + is_redirect(token) + 1, sizeof (char *));
	if (new_argv == NULL)
		return (NULL);
	while (old_argv[i])
	{
		new_argv[i] = ft_strdup(old_argv[i]);
		i++;
	}
	if (is_redirect(token))
	{
		new_argv[i] = ft_strdup(put_token(token));
		i++;
	}
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

char	**get_latestargv(t_cmd **head)
{
	int	index;
	t_cmd	*node;

	index = 0;
	node = *head;
	while(node)
	{
		if (node->next == NULL)
		{
			while (node->argv[index])
			{
				index++;
			}
			break ;
		}
		node = node->next;
	}
	return (&node->argv[index - 1]);
}

int	is_allspace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

t_cmd	*make_cmdlist(char *input)
{
	t_cmd	*head;
	t_cmd	*cmd;
	char	*word;
	char	*new_pos;
	int	token;
	int	state;

	head = NULL;
	cmd = NULL;
	new_pos = NULL;
	if (input == NULL)
		return (NULL);
	token = OTHER;
	state = NOT_Q;
	while ((new_pos = ft_min_strchr(input, &token)) >= input)
	{
		word = ft_strndup(input, new_pos - input + (new_pos == input));
		printf("** word:%s, token:%d, state:%d, input:%s, new_pos:%s ** \n", word, token, state, input, new_pos);
		if (state != NOT_Q && token != BR_DOUBLE)
		{
			printf("state != NOT_Q && token != BR_DOUBLE:%s\n", word);
			printf("latest argv:%s\n", *get_latestargv(&head));
			*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), word);
			if (new_pos != input)
				*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), put_token(token));
		}
		else if (cmd  && (is_redirect(cmd->op) || (cmd->op == BR_DOUBLE && state == NOT_Q )))
		{
			printf("append_arg:%s, is_allspace:%d\n", word, is_allspace(word));
			if (ft_isspace(word[0]))
			{
				printf("append_word:%s\n", word);
				if (!is_allspace(word))
				{
					if (append_arg(get_argv(word), &head) != 0)
						return (NULL);
				}
				printf("appned_token:%s\n", put_token(token));
				if (token == BR_DOUBLE)
				{
					if (append_arg(get_argv(put_token(token)), &head) != 0)
						return (NULL);
					state = DOUBLE_Q;
				}
			}
			else if (ft_strncmp(word, put_token(token), ft_strlen(word)))
			{
				printf("strjoin_word:%s, ft_strncmp:%d\n", word, ft_strncmp(word, put_token(token), ft_strlen(word)));
				*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), word);
			}
			cmd->op = get_op(new_pos);
		}
		else if (cmd && token == BR_DOUBLE && state == DOUBLE_Q)
		{
			printf("cmd && token == BR_DOUBLE, state == BR_DOUBLE:%s\n", word);
			*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), word);
			if (new_pos != input)
				*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), put_token(token));
			state = NOT_Q;
		}
		else
		{
			printf("else:%s\n", word);
			cmd = ft_cmdnew(get_argv(word), get_op(new_pos));
			ft_cmdadd_back(&head, cmd);
			if (cmd->op == BR_DOUBLE && state == NOT_Q)
			{
				printf("cmd && cmd->op == BR_DOUBLE:%s\n", word);
				if (ft_isspace(word[ft_strlen(word) - 1]))
				{
					if (append_arg(get_argv(ft_strdup("\"")), &head) != 0)
						return (NULL);
				}
				else
				{
					*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), put_token(token));
				}
				printf("NOT_Q->DOUBLE_Q\n");
				state = DOUBLE_Q;
			}
		}
		free(word);
		input = new_pos;
		if (input != NULL)
		{
			if (is_two_char(&token))
				input += 2;
			else
				input++;

		}
		if (ft_strlen(input) == 0)
			break;
		
	}
	if (state != NOT_Q)
	{
		ft_error_str("quote not closed\n");
	}
	ft_print_cmdlist(&head);
	return (head);
}
