#ifndef SHELL_H
# define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include <errno.h>

typedef struct	s_cmd
{
	struct s_cmd	*next;
	char		**argv;
	int		pid;
	int		op;
}		t_cmd;

/*
**shell.c
*/
int	main(int argc, char **argv, char **envp);

/*
**buildin.c
*/
int	isbuildin();

/*
**ft_cd.c
*/
int	ft_cd(char *path);

#endif
