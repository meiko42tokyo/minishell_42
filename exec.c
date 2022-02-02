#include "shell.h"

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2])
{
	pid_t	pid;
	int		newpipe[2];
	char	*input;
	int		re;

	re = 0;
	if (ispipe)
		pipe(newpipe);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork error", 2);
		ft_putstr_fd("\n", 2);
	}
	if (pid == 0)
	{
		reset_termcap();
		if (haspipe)
		{
			close(lastpipe[1]);
			dup2(lastpipe[0], 0);
			close(lastpipe[0]);
		}
		if (ispipe)
		{
			close(newpipe[0]);
			dup2(newpipe[1], 1);
			close(newpipe[1]);
		}
		input = *c->argv;
		re = do_execve(input, c->argv);
		if (re != 0)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(input, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (127);
		}
	}
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
	if (haspipe)
	{
		close(lastpipe[0]);
		close(lastpipe[1]);
	}
	if (ispipe)
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
	return (pid);
}

t_cmd	*do_pipeline(t_cmd *c)
{
	int	haspipe;
	int	lastpipe[2];

	haspipe = 0;
	lastpipe[0] = -1;
	lastpipe[1] = -1;
	while (c)
	{
		c->pid = start_command(c, ispipe(c), haspipe, lastpipe);
		haspipe = ispipe(c);
		if (haspipe)
			c = c->next;
		else
			break ;
	}
	return (c);
}

void	run_list(t_cmd *c, t_env *env)
{
	int	stat_loc;

	stat_loc = 0;
	while (c)
	{
		if (is_buildin(c->argv) && !ispipe(c))
		{
			g_shell->status = exec_buildin_parent(c->argv, env);
			c = c->next;
			continue ;
		}
		c = do_pipeline(c);
		waitpid(c->pid, &stat_loc, WUNTRACED);
		if (stat_loc == 32512)
			g_shell->status = 127;
		else if (stat_loc == 256)
			g_shell->status = 1;
		set_termcap();
		c = c->next;
	}
}
