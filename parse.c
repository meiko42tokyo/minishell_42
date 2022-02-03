#include "shell.h"

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

/*
static void	set_command(char *input, t_cmd *head, t_cmd *cmd, t_parse *ps)
{
	if ((ps->state != NOT_Q && !is_token_br(ps->token)) \
			|| (cmd && is_token_br(ps->token) && is_in_quoto(ps->state)))
		append_str(&head, ps->new_pos == input, ps);
	else if (cmd && is_token_br(cmd->op) && ps->state == NOT_Q)
		start_br(&head, &cmd, input, ps);
	else if (cmd && (is_redirect(cmd->op)))
		find_redirect(&head, &cmd, ps);
	else
		new_cmd(&head, &cmd, ps);
}
*/

/*
static void	set_input(char *input, t_parse *ps)
{
	input = ps->new_pos;
	skip_token(&input, ps);
	free(ps->word);
	ps->word = NULL;
	return ;
}
*/

t_cmd	*set_cmdlist(char *input, t_cmd *head, t_parse *ps)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (ps->new_pos >= input)
	{
		//set_command(input, head, cmd, ps);
		if ((ps->state != NOT_Q && !is_token_br(ps->token)) \
				|| (cmd && is_token_br(ps->token) && is_in_quoto(ps->state)))
			append_str(&head, ps->new_pos == input, ps);
		else if (cmd && is_token_br(cmd->op) && ps->state == NOT_Q)
			start_br(&head, &cmd, input, ps);
		else if (cmd && (is_redirect(cmd->op)))
			find_redirect(&head, &cmd, ps);
		else
			new_cmd(&head, &cmd, ps);
		//set_input(input, &ps);
		input = ps->new_pos;
		skip_token(&input, ps);
		free(ps->word);
		ps->word = NULL;
		if (ft_strlen(input) == 0)
			break ;
		else
			ps->new_pos = ft_min_strchr(input, &ps->token);
		if (ps->new_pos >= input)
			ps->word = ft_strndup(input, \
					ps->new_pos - input + (ps->new_pos == input));
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
	ft_print_cmdlist(&head);
	free(ps);
	//skip_heredoc(&head);
	expand(&head, env);
	return (head);
}
