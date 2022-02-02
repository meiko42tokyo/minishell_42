#include "shell.h"

void	print_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

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
		free(cp_name[i]);
		i++;
	}
	return ;
}

int	command_ex_check(char *command, int *r_status, int *t)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!ft_isalpha(command[i]) && command[i] != '_')
		{
			ft_putstr_fd("export `", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*r_status -= 1;
			*t += 1;
			return (-1);
		}
		i++;
	}
	return (0);
}
