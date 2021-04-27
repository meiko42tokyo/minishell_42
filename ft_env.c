#include "shell.h"

int	ft_env(char **environ)
{
	int			i;

	i = 0;
	while(environ[i])
	{
		ft_putstr_fd(environ[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
