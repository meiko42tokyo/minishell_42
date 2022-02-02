#include "shell.h"

int	expand_env(char **word, t_env *env, t_cmd *node, int arg_i)
{
	int		dis;
	int		env_hit;
	int		cur_pos;
	char	*exit_status;

	env_hit = 0;
	cur_pos = *word - node->argv[arg_i];
	if (*(*word + 1) == '?')
	{
		exit_status = get_exit_status();
		node->argv[arg_i] = set_new_arg(node->argv[arg_i], cur_pos, exit_status, *word + 2);
		free(exit_status);
		*word += 2;
		return (0);
	}
	dis = ft_strlen(*word + 1);
	find_min_dis(&dis, word);
	while (env)
	{
		if (ft_strncmp(*word + 1, env->name, dis) == 0)
		{
			node->argv[arg_i] = set_new_arg(node->argv[arg_i], cur_pos, env->value, *word + dis);
			env_hit = 1;
		}
		env = env->next;
	}
	if (env_hit == 0)
	{
		if (strnshift(*word, dis, node->argv[arg_i]))
			return (1);
	}
	*word = node->argv[arg_i];
	(*word)[ft_strlen(*word)] = '\0';
	*word += cur_pos;
	return (0);
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
		{
			*word = *(word + 1);
			word++;
			strshift(word);
		}
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
