#include "shell.h"

int	ispipe(t_cmd *c)
{
	if (c->op == 124)
		return (1);
	return (0);
}

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2], char **environ)
{
	pid_t	pid;
	int	newpipe[2];
	char *path;
	char *input;
	int exec;
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
		exec = execve(path, c->argv, environ); // exec needed?
		if (errno){
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			exit(errno);
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


t_cmd	*do_pipeline(t_cmd *c, char **environ)
{
	int	haspipe;
	int	lastpipe[2];

	haspipe = 0;
	lastpipe[0] = -1;
	lastpipe[1] = -1;
	while (c)
	{
		c->pid = start_command(c, ispipe(c), haspipe, lastpipe, environ);
		haspipe = ispipe(c);
		if (haspipe)
			c = c->next;
		else
			break;
	}
	return (c);
}


void	run_list(t_cmd *c, char **environ)
{
	while (c)
	{
		if (is_buildin(c->argv) && !ispipe(c))
		{
			exec_buildin(c->argv, environ);
			c = c->next;
			continue;
		}
		c = do_pipeline(c, environ);
		//waitpid(c->pid);
		//printf("node:%s, %c\n", *c->argv, c->op); 
		c = c->next;
	}
}

int	main(int argc, char **argv) 
{
	char *input;
	t_cmd	*head;
	extern char	**environ;

	argc = 1;
	argv = NULL;
	signal(SIGINT, SIG_IGN);
	while (1) {
		ft_putstr_fd("> ", 0);
		get_next_line(0, &input); // TODO: if fail in GNL
		// save input to doubly linked list
		head = make_cmdlist(input);
		signal(SIGINT, SIG_DFL);
		run_list(head, environ);
		free(input);
	}
	return (0);
}
