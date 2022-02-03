#include "shell.h"

static void	word_shift(char *word)
{
	*word = *(word + 1);
	word++;
	strshift(word);
}

int	check_word(char *word, t_env *env, t_cmd *node, int arg_i)
{
	int	state;

	state = NOT_Q;
	while (*word)
	{
		if (*word == '\'' || *word == '\"')
			br(&state, &word);
		else if (*word == '\\' && is_escape(*(word + 1)) && state == DOUBLE_Q)
			word_shift(word);
		else if (*word == '$' && state != SINGLE_Q)
		{
			if (expand_env(&word, env, node, arg_i))
				return (1);
		}
		else
		{
			if (*word == '\0')
				break ;
			word++;
		}
	}
	return (0);
}

void	expand(t_cmd **head, t_env *env)
{
	t_cmd	*node;
	int		arg_i;

	node = *head;
	arg_i = 0;
	while (node)
	{
		arg_i = 0;
		while (node->argv[arg_i])
		{
			if (check_word(node->argv[arg_i], env, node, arg_i))
				strpshift(node->argv, arg_i);
			arg_i++;
		}
		if (node->next == NULL)
			break ;
		node = node->next;
	}	
}
