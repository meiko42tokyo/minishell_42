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

typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**argv;
	pid_t			pid;
	int				op;
	int				status;
}		t_cmd;

typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
}		t_env;

typedef struct s_line
{
	struct s_line	*next;
	struct s_line	*prev;
	char			*data;
}		t_line;

typedef struct s_parse
{
	int		state;
	int		token;
	char	*new_pos;
	char	*word;
}		t_parse;

typedef struct s_shell
{
	int				status;
	char			*line;
	t_line			*dhead;
	t_line			*cur_node;
	struct termios	term;
	struct termios	term_origin;
}		t_shell;

extern t_shell	*g_shell;

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

/*
**exec_utils.c
*/
int		ispipe(t_cmd *c);
char	**make_split_path(char **environ);
char	*make_path(char *input, char **split_path, int i);
int	do_execve(char *input, char **argv);

/*
**lstUtils.c
*/
void	ft_print_cmdlist(t_cmd **head);
void	free_cmdlist(t_cmd **head);

/*
**lstUtils.c
*/
t_cmd	*ft_cmdnew(char *argv[], int op);
void	ft_cmdadd_back(t_cmd **head, t_cmd *new);
int		ft_argv_len(t_cmd *cmd);
int		check_argvsize(t_cmd *node);
int		ft_print_cmdsize(t_cmd **head);

/*
**doubly_lstUtils.c
*/
t_line	*ft_linenew(char *data);
int		ft_lineadd_back(t_line **head, t_line *new);
int		ft_get_lstsize(t_line **head);
char	*ft_get_latestdata(t_line **head);
void	ft_change_latestline(t_line **head, char *line);
void	ft_free_linehead(t_line **head);
void	ft_print_linelist(t_line **head, t_line **cur_node);

/*
**termcap.c
*/
int		get_line(void);
int		update_and_make_empty_node(void);

/*
**termcap_utils.c
*/
int		ft_putchar(int c);
void	init_termcap(void);
void	set_termcap(void);
void	reset_termcap(void);
char	*make_line(char *line, int c_int);

/*
**termcap_utils2.c
*/
char	*history_out(t_line **cur_node, int c);
int	update_and_make_newnode(t_line **head, t_line **cur_node, char *line);
int	update_and_make_empty_node(void);
int	new_line(void);

/*
**syntax_error.c
*/
int		syntax_error(char **input);

/*
**heredoc.c
*/
int		heredoc(char **input);

/*
**token_util.c
*/
char	**set_ops(void);
int		get_op(char *op);
char	*put_token(int token);

/*
**token_classify_utils.c
*/
int		is_op(int *token);
int		is_redirect(int token);
int		is_two_char(int *token);
int		is_token_br(int token);

/*
**state_manage.c
*/
int		is_in_quoto(int state);
void	manage_state(int *state, char c);
/*
**parse.c
*/
char	**get_argv(char *input);
t_cmd	*make_cmdlist(char *input, t_env *env);

/*
**expand.c
*/
void	expand(t_cmd **head, t_env *env);
void	br(int *state, char **word);

/*
**expand_utils.c
*/
void	strshift(char *word);
void	ft_mempshift(char **dst, char **src, size_t len);
void	strpshift(char **argv, int arg_i);
int		strnshift(char *word, int dis, char *head);
int		is_escape(char c);

/*
**expand_utils.c
*/
void	br(int *state, char **word);
char	*set_env_ops(void);
char	*set_new_arg(char *head, int cur_pos, char *env_val, char *left_word);
void	find_min_dis(int *dis, char **word);
char	*get_exit_status(void);

/*
**buildin.c
*/
int		exec_buildin(char **command, t_env *env);
int		is_buildin(char **command);
int		exec_buildin_parent(char **command, t_env *env);

/*
**buildin_command
*/
int		ft_cd(char *path, t_env *env);
int		ft_pwd(void);
int		include_redir(char **command);
int		ft_echo(char **command);
int		ft_exit(char **command);
int		ft_env(t_env *env, char **command);
int		ft_export(char **command, t_env *env);
int		ft_unset(char **command, t_env *env);
int		ft_env_unset(t_env **env, char *name);

/*
**ft_export_utils.c
*/
void	put_value(t_env *tmp);
void	swap(char **s1, char **s2);
int		sort_env(char **cp_name);
int		dup_env(t_env *env, char **cp_name);
int		export_env(t_env *env);
void	print_env(t_env *env, char **cp_name);
int		command_ex_check(char *command, int *r_status, int *t);

/*
**redirect.c
*/
int		is_redir(char *command);
char	**ft_redirect(char **command, int *in, int *out);
char	**return_free(char **command);

/*
**env_utils.c
*/
void	ft_envadd_back(t_env **env, t_env *new);
t_env	*init_env(void);
void	env_free(t_env *env);
void	env_all_free(t_env *env);

/*
**signal.c
*/
void	signal_handler(int signo);
void	signal_handler_child(int signo);

/*
**errnor.c
*/
int		ft_errno(int num);
int		ft_error_str(char *str);

#endif
