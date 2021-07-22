#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <termcap.h>
# include <termios.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include "libft/libft.h"

# define EOF_KEY 4
# define AR_U 4283163
# define AR_D 4348699

# define OP_SEP 0
# define OP_PIPE 1
# define RD_LESSER 2
# define RD_GREATER 3
# define RD_EXTRACT 4
# define RD_INSERT 5
# define BR_DOUBLE 6
# define BR_SINGLE 7
# define OTHER -1
# define OPS_SIZE 8
# define ENV_OPS_SIZE 3

# define NOT_Q 0
# define SINGLE_Q 1
# define DOUBLE_Q 2

extern int	status;

typedef struct s_cmd
{
	struct s_cmd	*next;
	char		**argv;
	pid_t		pid;
	int		op;
	int		status;
}		t_cmd;

typedef struct	s_env
{
	struct s_env	*next;
	char		*name;
	char		*value;
}		t_env;

typedef struct s_line
{
	struct s_line	*next;
	struct s_line	*prev;
	char		*data;
}		t_line;

/*
**shell.c
*/
//int	main(int argc, char **argv, char **envp);

/*
**exec.c
*/
void	run_list(t_cmd *c, t_env *env);
t_cmd	*do_pipeline(t_cmd *c);
pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2]);
int 	ispipe(t_cmd *c);

/*
**lstUtils.c
*/
t_cmd	*ft_cmdnew(char *argv[], int op);
void	ft_cmdadd_back(t_cmd **head, t_cmd *new);
int	ft_print_cmdsize(t_cmd **head);
void	ft_print_cmdlist(t_cmd **head);

/*
**doubly_lstUtils.c
*/
t_line	*ft_linenew(char *data);
int	ft_lineadd_back(t_line **head, t_line *new);
int	ft_get_lstsize(t_line **head);
char	*ft_get_latestdata(t_line **head);
void	ft_change_latestline(t_line **head, char *line);
void	ft_free_linehead(t_line **head);

/*
**termcap.c
*/
int	get_line(char *line, t_line **head, t_line **cur_node);
void	set_termcap(struct termios *term);
void	reset_termcap(struct termios *term);

/*
**syntax_error.c
*/
int	valid_syntax(char *input);

/*
**parse.c
*/
char	**get_argv(char *input);
t_cmd	*make_cmdlist(char *input, t_env *env);

/*
**expand.c
*/
void	expand(t_cmd **head, t_env *env);

/*
**buildin.c
*/
int	exec_buildin(char **command, t_env *env);
int	is_buildin(char **command);

/*
**buildin_command
*/
int	ft_cd(char *path, t_env *env);
int	ft_pwd();
int	ft_echo(char **command);
int	ft_exit(char **command);
int	ft_env(t_env *env);
int	ft_export(char **command, t_env *env);
int	ft_unset(char **command, t_env *env);

/*
**redirect.c
*/
int	is_redir(char *command);
char	**ft_redirect(char **command, int *in, int *out);

/*
**env_utils.c
*/
void	ft_envadd_back(t_env **env, t_env *new);
t_env	*init_env();
void	env_free(t_env *env);

/*
**errnor.c
*/
int	ft_errno(int num);
int	ft_error_str(char *str);

#endif
