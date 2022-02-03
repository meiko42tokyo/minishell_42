#include "shell.h"

void	start_command_child(t_cmd *c, int haspipe, int lastpipe[2])
{
	char	*input;
	int		re;

	re = 0;
	if (haspipe)
	{
		dup2(lastpipe[0], 0);
		multi_close(&lastpipe[0], &lastpipe[1], NULL, NULL);
	}
	reset_termcap();
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

void	start_command_after(int ispipe, int haspipe, int lastpipe[2], int newpipe[2])
{
	if (g_shell->heredoc_fd[0] > 0)
		multi_close(&g_shell->heredoc_fd[0], &g_shell->heredoc_fd[1], NULL, NULL);
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
	if (haspipe)
		multi_close(&lastpipe[0], &lastpipe[1], NULL, NULL);
	if (ispipe)
	{
		lastpipe[0] = newpipe[0];
		lastpipe[1] = newpipe[1];
	}
}

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2])
{
	pid_t	pid;
	int		newpipe[2];

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
		if (ispipe)
		{
			dup2(newpipe[1], 1);
			multi_close(&newpipe[0], &newpipe[1], NULL, NULL);
		}
		start_command_child(c, haspipe, lastpipe);
	}
	start_command_after(ispipe, haspipe, lastpipe, newpipe);
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
