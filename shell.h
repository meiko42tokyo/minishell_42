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
# include <sys/ioctl.h>
# include "libft/libft.h"

# define EOF_KEY 4
# define AR_U 4283163
# define AR_D 4348699

# define OP_SEP 1
# define OP_PIPE 2
# define OP_OTHER -1

typedef struct s_cmd
{
	struct s_cmd	*next;
	char		**argv;
	pid_t		pid;
	int		op;
}		t_cmd;

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
void	run_list(t_cmd *c);
t_cmd	*do_pipeline(t_cmd *c);
pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2]);
int 	ispipe(t_cmd *c);

/*
**lstUtils.c
*/
t_cmd	*ft_cmdnew(char *argv[], int op);
void	ft_cmdadd_back(t_cmd **head, t_cmd *new);
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
int	ft_pwd(void);

#endif
