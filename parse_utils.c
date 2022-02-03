#include "shell.h"

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

static void	ps_judge(t_cmd **head, char *input, char *tmp, t_parse *ps)
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
	return ;
}

void	start_br(t_cmd **head, t_cmd **cmd, char *input, t_parse *ps)
{
	char	*tmp;

	tmp = NULL;
	if (ft_isspace(ps->word[0]))
		word_start_space(head, ps);
	else if (ft_strncmp(ps->word, put_token(ps->token), \
				ft_strlen(put_token(ps->token))))
		ps_judge(head, input, tmp, ps);
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
