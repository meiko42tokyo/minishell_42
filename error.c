#include "shell.h"

int	ft_errno(int num)
{
	ft_putstr_fd(strerror(num), 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}
