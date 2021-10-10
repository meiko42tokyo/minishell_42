#include "shell.h"

int	ispipe(t_cmd *c)
{
	if (c->op == OP_PIPE)
		return (1);
	return (0);
}

static int	do_execve(char *input, char **argv)
{
	extern char **environ;
	char	**split_path;
	char	*path;
	char	*tmp;
	int		i;

	split_path = NULL;
	i = 0;
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
		path = ft_strjoin(tmp, input);
		if (!execve(path, argv, environ))
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	return (-1);
}

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2])
{
	pid_t	pid;
	int	newpipe[2];
	char *input;
	int	stat_loc;

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
		input = *c->argv; // TODO:input->c->argv[0]
		g_status = do_execve(input, c->argv); // exec needed?
		if (g_status == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
	} else {
		waitpid(pid, &stat_loc, WUNTRACED);
	}
	//printf("stat:%d\n", stat_loc);
	if (stat_loc != 0)
		g_status = 127;
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
			break;
	}
	return (c);
}

void	run_list(t_cmd *c, t_env *env)
{
	while (c)
	{
		if (is_buildin(c->argv) && !ispipe(c))
		{
			g_status = exec_buildin(c->argv, env);
			c = c->next;
			continue;
		}
		c = do_pipeline(c);
		//waitpid(c->pid);
		//printf("node:%s, %c\n", *c->argv, c->op); 
		c = c->next;
	}
}
