#include "shell.h"

void	multi_close(int *fd1, int *fd2, int *fd3, int *fd4)
{
	if (fd1)
		close(*fd1);
	if (fd2)
		close(*fd2);
	if (fd3)
		close(*fd3);
	if (fd4)
		close(*fd4);
}
