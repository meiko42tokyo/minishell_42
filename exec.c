#include "shell.h"

int	ispipe(t_cmd *c)
{
	if (c->op == OP_PIPE)
		return (1);
	return (0);
}

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2])
{
	pid_t	pid;
	int	newpipe[2];
	char *path;
	char *input;
	extern char **environ; 
	int	stat_loc;

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
		path = ft_strjoin("/bin/", input);
		errno = 0;
		execve(path, c->argv, environ); // exec needed?
		if (errno){
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(&input[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			status = COMMAND_ERROR;
			printf("status_fail_execve:%d\n", status);
			return (pid);
			//これ消して大丈夫KA確認exit(COMMAND_ERROR);
		}
	} else {
		waitpid(pid, &stat_loc, WUNTRACED);
	}
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
			status = exec_buildin(c->argv, env);
			c = c->next;
			continue;
		}
		c = do_pipeline(c);
		//waitpid(c->pid);
		//printf("node:%s, %c\n", *c->argv, c->op); 
		c = c->next;
	}
}
