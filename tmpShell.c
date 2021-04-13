#include "shell.h"

int	isbuiltin(t_cmd *c)
{
	// Temporary always return false.
	// TODO: Should be judged by type of command
	if (c->argv)
		return (0);
	return (0);
}

int	ispipe(t_cmd *c)
{
	if (c->op == 124)
		return (1);
	return (0);
}

pid_t	start_command(t_cmd *c, int ispipe, int haspipe, int lastpipe[2])
{
	pid_t	pid;
	int	newpipe[2];
	char *path;
	char *input;
	int exec;
	extern char **environ; 
	//int	stat_loc;

	if (ispipe)
		pipe(newpipe);
	pid = fork();
	if (pid == 0)
	{
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
		path = ft_strjoin("/bin/", input);
		exec = execve(path, c->argv, environ);
		printf("path:%s\n", path);
		printf("exec:%d\n", exec);
		// TODO: Should change into our own functions
		printf("accepted command %s in pid %d!\n", *c->argv, getpid());
	}
	// ?
	//waitpid(pid, &stat_loc, WUNTRACED);
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


void	run_list(t_cmd *c)
{
	while (c)
	{
		if (isbuiltin(c) && !ispipe(c))
		{
			//execve(c);
			c = c->next;
			continue;
		}
		c = do_pipeline(c);
		//waitpid(c->pid);
		printf("node:%s, %c\n", *c->argv, c->op); 
		c = c->next;
	}
}

char **get_input(char *input) {
	char **command = malloc(8 * sizeof(char *));
	if (command == NULL)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	char *separator = " ";
	char *parsed;
	int index = 0;

	parsed = strtok(input, separator);
	while (parsed != NULL) {
		command[index] = parsed;
		index++;
		
		parsed = strtok(NULL, separator);
	}
	command[index] = NULL;
	return command;
}

int	main(int argc, char **argv, char **envp) 
{
	char **command;
	char *input;
	char *path;
	t_cmd	*head;
	pid_t child_pid;
	int stat_loc;

	argc = 1;
	argv = NULL;
	signal(SIGINT, SIG_IGN);
	while (1) {
		ft_putstr_fd("> ", 0);
		get_next_line(0, &input);
		command = get_input(input);
		path = ft_strjoin("/bin/", input); // not command?
		head = ft_cmdnew(command, 0); // should be dynamic depend on op
		errno = 0;
		if (is_buildin(command) == 0) // should change strcmp?
			continue ;
		child_pid = fork();
		if (child_pid < 0)
		{
			ft_putstr_fd("fork error", 2);
			ft_putstr_fd("\n", 2);
		}
		if (child_pid == 0) {
			signal(SIGINT, SIG_DFL);
			errno = 0;
			execve(path, command, envp);
			if (errno){
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				exit(errno);
			}
		} else {
			waitpid(child_pid, &stat_loc, WUNTRACED);
		}
		free(input);
		free(command);
	}
	return (0);
//	run_list(head);

	// debug
	/*
	while (head)
	{
		if (head->next == NULL)
			break;
		head=head->next;
	}
	*/
}
