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

typedef struct	s_env
{
	struct s_env	*next;
	char		*name;
	char		*value;
}		t_env;

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
**parse.c
*/
char	**get_argv(char *input);
t_cmd	*make_cmdlist(char *input);

/*
**buildin.c
*/
int	exec_buildin(char **command, t_env *env);
int	is_buildin(char **command);

/*
**buildin_command
*/
int	ft_cd(char *path);
int	ft_pwd();
int	ft_echo(char **command);
int	ft_exit(char **command);
int	ft_env(t_env *env);
int	ft_export(char **command, t_env *env);
int	ft_unset(char **command, t_env *env);

/*
**env_utils.c
*/
void	ft_envadd_back(t_env **env, t_env *new);
t_env	*init_env();
void	env_free(t_env *env);
t_env	*dup_env(t_env *env);

/*
**errnor.c
*/
int	ft_errno(int num);
int	ft_error_str(char *str);

#endif
