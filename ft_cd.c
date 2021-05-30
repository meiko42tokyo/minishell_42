#include "shell.h"

int	ft_cd(char *path)
{
	if (chdir(path) < 0)
		return (ft_errno(errno));
	return (0);
}
