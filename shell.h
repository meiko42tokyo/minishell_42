#ifndef SHELL_H
# define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <termcap.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <sys/ioctl.h>
#include "libft/libft.h"

typedef struct	s_cmd
{
	struct s_cmd	*next;
	char		**argv;
	pid_t		pid;
	int		op;
}		t_cmd;

typedef struct	s_line
{
	struct s_line	*next;
	struct s_line	*prev;
	char			*data;
}		t_line;

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
**doubly_lstUtils.c
*/
t_line	*ft_linenew(char *data);
void	ft_lineadd_back(t_line **head, t_line *new);

/*
**parse.c
*/
char	**get_argv(char *input);
t_cmd	*make_cmdlist(char *input);

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
