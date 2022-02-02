#include "shell.h"

int	ispipe(t_cmd *c)
{
	if (c->op == OP_PIPE)
		return (1);
	return (0);
}

static int	do_execve(char *input, char **argv)
{
	extern char	**environ;
	char		**split_path;
	char		*path;
	char		*tmp;
	int			i;
	int			t;

	split_path = NULL;
	i = 0;
	t = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH", 4))
		{
			tmp = ft_strdup(environ[i] + 5);
			split_path = ft_split(tmp, ':');
			i = 0;
			free(tmp);
			break ;
		}
		i++;
	}
	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		t = ft_strncmp(input, split_path[i], ft_strlen(split_path[i]));
		free(split_path[i]);
		if (t != 0)
			path = ft_strjoin(tmp, input);
		else
			path = input;
		free(tmp);
		if (include_redir(argv))
			argv = ft_redirect(argv, NULL, NULL);
		if (!execve(path, argv, environ))
			return (0);
		i++;
		//execve(path, argv, environ);
		free(path);
	}
	free(split_path);
	return (-1);
}

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2])
{
	pid_t	pid;
	int		newpipe[2];
	char	*input;
	int		stat_loc;

	stat_loc = 0;
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
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
		if (include_redir(c->argv))
			c->argv = ft_redirect(c->argv, NULL, NULL);
		if (!c->argv)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit(1);
		}
		input = *c->argv; // TODO:input->c->argv[0]
		g_shell->status = do_execve(input, c->argv); // exec needed?
		if (g_shell->status == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
	}
	if (stat_loc != 0)
		g_shell->status = 127;
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
	while (c)
	{
		if (is_buildin(c->argv) && !ispipe(c))
		{
			g_shell->status = exec_buildin_parent(c->argv, env);
			c = c->next;
			continue ;
		}
		c = do_pipeline(c);
		waitpid(c->pid, NULL, 0);
		c = c->next;
	}
}
