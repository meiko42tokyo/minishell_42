#include "shell.h"

int	ft_errno(int num)
{
	ft_putstr_fd(strerror(num), 2);
	ft_putstr_fd("\n", 2);
	//終了コードをいれる
	return (-1);
}

int	ft_error_str(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	//終了コードいれる
	return (-1);
}
