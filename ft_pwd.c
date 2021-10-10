#include "shell.h"

int	ft_pwd(void)
{
	size_t	size;
	char	*buf;

	size = 1024;
	buf = malloc(size);
	if (!buf)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	//エラー処理追記
	if (!getcwd(buf, size))
		return (ft_errno(errno));
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	free(buf);
	return (0);
}
