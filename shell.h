#ifndef SHELL_H
# define SHELL_H
// Temporary aim at checking structure and use tmpShell.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "libft/libft.h"

typedef struct	s_cmd
{
	struct s_cmd	*next;
	char		**argv;
	pid_t		pid;
	int		op;
}		t_cmd;

/*
**shell.c
*/
//int	main(int argc, char **argv, char **envp);

/*
**lstUtils.c
*/
t_cmd	*ft_cmdnew(char *argv[], int op);
void	ft_cmdadd_back(t_cmd **head, t_cmd *new);

/*
**buildin.c
*/
int	exec_buildin(char **command);
int	is_buildin(char **command);

/*
**ft_cd.c
*/
int	ft_cd(char *path);

/*
**ft_pwd.c
*/
int	ft_pwd();

#endif
