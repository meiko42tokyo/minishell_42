#include "shell.h"

extern int	status;

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
	char 	**ops; 
	int	index;

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
	return (input + min_dis);;
}

size_t	ft_strplen(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	free_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**copy_argvs(char *argv[], char **old_argv, size_t len, int token)
{
	char	**new_argv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_argv = (char**)malloc(sizeof (char *) * (len + is_redirect(token) + 1));
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
		new_argv[i] = argv[j];
		i++;
		j++;
	}
	new_argv[i] = NULL;
	free_argv(old_argv);
	free(argv);
	return (new_argv);
}

int		append_arg(char *argv[], t_cmd **head)
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

void	append_str(t_cmd **head, int left, t_parse *ps)
{
	char	*tmp;	

	tmp = *get_latestargv(head);
	*get_latestargv(head) = ft_strjoin(tmp, ps->word);
	free(tmp);
	if (!left)
	{
		tmp = *get_latestargv(head);
		*get_latestargv(head) = ft_strjoin(tmp, put_token(ps->token));
		free(tmp);	
	}
	if (is_token_br(ps->token))
		ps->state = NOT_Q;
}

void	word_start_space(t_cmd **head, t_parse *ps)
{
	if (!is_allspace(ps->word))
	{
		if (append_arg(get_argv(ps->word), head) != 0)
		{
			*head = NULL;
			return ;
		}
	}
	if (is_token_br(ps->token))
	{
		if (append_arg(get_argv(put_token(ps->token)), head) != 0)
		{
			*head = NULL;
			return ;
		}
		if (ps->token == BR_DOUBLE)
			ps->state = DOUBLE_Q;
		else if (ps->token == BR_SINGLE)
			ps->state = SINGLE_Q;
	}
}

void	start_br(t_cmd **head, t_cmd **cmd, char *input, t_parse *ps)
{
	char	*tmp;
	if (ft_isspace(ps->word[0]))
		word_start_space(head, ps);
	else if (ft_strncmp(ps->word, put_token(ps->token), ft_strlen(put_token(ps->token))))
	{
		tmp = *get_latestargv(head);
		*get_latestargv(head) = ft_strjoin(tmp, ps->word);
		free(tmp);
		if (ps->new_pos != input)
		{
			tmp = *get_latestargv(head);
			*get_latestargv(head) = ft_strjoin(tmp, put_token(ps->token));
			free(tmp);
		}
		if (ps->token == BR_DOUBLE)
			ps->state = DOUBLE_Q;
		else if (ps->token == BR_SINGLE)
			ps->state = SINGLE_Q;
	}
	else
	{
		tmp = *get_latestargv(head);
		*get_latestargv(head) = ft_strjoin(tmp, ps->word);
		free(tmp);
		if (ps->token == BR_DOUBLE)
			ps->state = DOUBLE_Q;
		else if (ps->token == BR_SINGLE)
			ps->state = SINGLE_Q; 
	}
	(*cmd)->op = get_op(ps->new_pos);
	ft_print_cmdlist(head);
}

void	find_redirect(t_cmd **head, t_cmd **cmd, t_parse *ps)
{
	if (append_arg(get_argv(ps->word), head) != 0)
	{
		*head = NULL;
		return ;
	}
	(*cmd)->op = get_op(ps->new_pos);
}

void	new_cmd(t_cmd **head, t_cmd **cmd, t_parse *ps)
{
	char	*tmp;

	*cmd = ft_cmdnew(get_argv(ps->word), get_op(ps->new_pos));
	ft_cmdadd_back(head, *cmd);
	if (is_token_br((*cmd)->op) && ps->state == NOT_Q)
	{
		if (ft_isspace(ps->word[ft_strlen(ps->word) - 1]))
		{
			if (append_arg(get_argv(put_token(ps->token)), head) != 0)
			{
				return ;
			}
		}
		else
		{
			tmp = *get_latestargv(head);
			*get_latestargv(head) = ft_strjoin(tmp, put_token(ps->token));
			free(tmp);
		}
		if (ps->token == BR_DOUBLE)
			ps->state = DOUBLE_Q;
		else if (ps->token == BR_SINGLE)
			ps->state = SINGLE_Q;
	}
}

void	skip_token(char **input, t_parse *ps)
{
	if (**input != '\0')
	{
		if (is_two_char(&ps->token))
			*input += 2;
		else
			*input += 1;
	}
}

t_cmd	*set_cmdlist(char *input, t_cmd *head, t_parse *ps)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (ps->new_pos >= input)
	{
		if ((ps->state != NOT_Q && !is_token_br(ps->token)) || (cmd && is_token_br(ps->token) && is_in_quoto(ps->state)))
			append_str(&head, ps->new_pos == input, ps);
		else if (cmd && is_token_br(cmd->op) && ps->state == NOT_Q )
			start_br(&head, &cmd, input, ps);
		else if (cmd && (is_redirect(cmd->op)))
			find_redirect(&head, &cmd, ps);
		else
			new_cmd(&head, &cmd, ps);
		input = ps->new_pos;
		skip_token(&input, ps);
		free(ps->word);
		ps->word = NULL;
		if (ft_strlen(input) == 0)
			break;	
		else
			ps->new_pos = ft_min_strchr(input, &ps->token);
		if (ps->new_pos >= input)
			ps->word = ft_strndup(input, ps->new_pos - input + (ps->new_pos == input));
	}
	return (head);
}

t_cmd	*make_cmdlist(char *input, t_env *env)
{
	t_cmd	*head;
	t_parse	*ps;

	head = NULL;
	if (input == NULL)
		return (NULL);
	ps = (t_parse *)malloc(sizeof(t_parse));
	ps->state = NOT_Q;
	ps->token = OTHER;
	ps->new_pos = ft_min_strchr(input, &ps->token);
	ps->word = ft_strndup(input, ps->new_pos - input + (ps->new_pos == input));
	head = set_cmdlist(input, head, ps);
	free(ps);
	//ft_print_cmdlist(&head);
	expand(&head, env);
	return (head);
}
