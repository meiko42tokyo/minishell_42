#include "shell.h"

int	ft_cd(char *path)
{
	if (chdir(path) < 0)
	{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (-1);
	}
	return (0);
}
