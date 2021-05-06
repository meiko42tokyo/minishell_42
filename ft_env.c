#include "shell.h"

int	ft_env(t_env *env)
{
	int			i;

	i = 0;
	while(env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	return (0);
}
