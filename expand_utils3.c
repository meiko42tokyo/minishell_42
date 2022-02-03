#include "shell.h"

static int	word_judge(int *cur_pos, char **word, t_cmd *node, int arg_i)
{
	char	*exit_status;

	*cur_pos = *word - node->argv[arg_i];
	if (*(*word + 1) == '?')
	{
		exit_status = get_exit_status();
		node->argv[arg_i] = set_new_arg(node->argv[arg_i], \
				*cur_pos, exit_status, *word + 2);
		free(exit_status);
		*word = node->argv[arg_i];
		(*word)[ft_strlen(*word)] = '\0';
		*word += *cur_pos;
		return (1);
	}
	return (0);
}

static void	word_set(char **word, t_cmd *node, int cur_pos, int arg_i)
{
	*word = node->argv[arg_i];
	(*word)[ft_strlen(*word)] = '\0';
	*word += cur_pos;
}

int	expand_env(char **word, t_env *env, t_cmd *node, int arg_i)
{
	int		dis;
	int		env_hit;
	int		cur_pos;

	env_hit = word_judge(&cur_pos, word, node, arg_i);
	if (env_hit != 0)
		return (0);
	dis = ft_strlen(*word + 1);
	find_min_dis(&dis, word);
	while (env)
	{
		if (ft_strncmp(*word + 1, env->name, dis) == 0)
		{
			node->argv[arg_i] = set_new_arg(node->argv[arg_i], \
					cur_pos, env->value, *word + dis);
			env_hit = 1;
		}
		env = env->next;
	}
	if (env_hit == 0)
	{
		if (strnshift(*word, dis, node->argv[arg_i]))
			return (1);
	}
	word_set(word, node, cur_pos, arg_i);
	return (0);
}
