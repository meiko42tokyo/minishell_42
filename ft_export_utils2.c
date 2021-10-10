#include "shell.h"

void	print_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

	tmp = (t_env *)malloc(sizeof(t_env));
	i = 0;
	while (cp_name[i])
	{
		tmp = env;
		while (tmp)
		{
			if ((ft_strcmp(cp_name[i], tmp->name) == 0) && \
					ft_strcmp(cp_name[i], "_") != 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->name, 1);
				if (tmp->value)
					put_value(tmp);
				ft_putstr_fd("\n", 1);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return ;
}
