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
		new_argv[i] = ft_strdup(argv[j]);
		i++;
		j++;
	}
	new_argv[i] = NULL;
	free_argv(old_argv);
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

void	append_str()
{
}

void	pattern2()
{
}

void	pattern3()
{
}

void	new_cmd()
{
}

t_cmd	*set_cmdlist(char *input, t_cmd *head, char *new_pos)
{
	char	*word;
	int	state;
	int	token;
	t_cmd	*cmd;

	state = NOT_Q;
	token = OTHER;
	cmd = NULL;
	while (new_pos >= input)
	{
		word = ft_strndup(input, new_pos - input + (new_pos == input));
		if ((state != NOT_Q && !is_token_br(token)) || (cmd && is_token_br(token) && is_in_quoto(state)))
			append_str();
		else if (cmd && is_token_br(cmd->op) && state == NOT_Q )
			pattern2();
		else if (cmd && (is_redirect(cmd->op)))
			pattern3();
		else
			new_cmd();
			
	}
	return (head);
}

t_cmd	*make_cmdlist(char *input, t_env *env)
{
	t_cmd	*head;
	char	*new_pos;
	int	token;

	head = NULL;
	token = OTHER;
	if (input == NULL)
		return (NULL);
	new_pos = ft_min_strchr(input, &token);
	set_cmdlist(input, head, new_pos);
	expand(&head, env);
	return (head);
}

t_cmd	*mmake_cmdlist(char *input, t_env *env)
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
		if ((state != NOT_Q && !is_token_br(token)) || (cmd && is_token_br(token) && is_in_quoto(state)))
		{
			*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), word);
			if (new_pos != input)
				*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), put_token(token));
			if (is_token_br(token))
				state = NOT_Q;
		}
		else if (cmd && is_token_br(cmd->op) && state == NOT_Q )
		{
			if (ft_isspace(word[0]))
			{
				if (!is_allspace(word))
				{
					if (append_arg(get_argv(word), &head) != 0)
						return (NULL);
				}
				if (is_token_br(token))
				{
					if (append_arg(get_argv(put_token(token)), &head) != 0)
						return (NULL);
					if (token == BR_DOUBLE)
						state = DOUBLE_Q;
					else if (token == BR_SINGLE)
						state = SINGLE_Q;
				}
			}
			else if (ft_strncmp(word, put_token(token), ft_strlen(put_token(token))))
			{
				*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), word);
				if (new_pos != input)
					*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), put_token(token));
				if (token == BR_DOUBLE)
					state = DOUBLE_Q;
				else if (token == BR_SINGLE)
					state = SINGLE_Q;
			}
			else
			{
				*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), word);
				if (token == BR_DOUBLE)
					state = DOUBLE_Q;
				else if (token == BR_SINGLE)
					state = SINGLE_Q; 
			}
			cmd->op = get_op(new_pos);
		}
		else if (cmd && (is_redirect(cmd->op)))
		{
			if (append_arg(get_argv(word), &head) != 0)
				return (NULL);
			cmd->op = get_op(new_pos);
		}
		else
		{
			cmd = ft_cmdnew(get_argv(word), get_op(new_pos));
			ft_cmdadd_back(&head, cmd);
			if (is_token_br(cmd->op) && state == NOT_Q)
			{
				if (ft_isspace(word[ft_strlen(word) - 1]))
				{
					if (append_arg(get_argv(put_token(token)), &head) != 0)
						return (NULL);
				}
				else
				{
					*get_latestargv(&head) = ft_strjoin(*get_latestargv(&head), put_token(token));
				}
				if (token == BR_DOUBLE)
					state = DOUBLE_Q;
				else if (token == BR_SINGLE)
					state = SINGLE_Q;
			}
		}
		free(word);
		input = new_pos;
		if (*input != '\0')
		{
			if (is_two_char(&token))
				input += 2;
			else
				input++;
		}
		if (ft_strlen(input) == 0)
		{
			break;
		}
		
	}
	if (state != NOT_Q)
	{
		ft_error_str("quote not closed\n"); // need to think about better error
	}
	expand(&head, env);
	//ft_print_cmdlist(&head);
	return (head);
}
