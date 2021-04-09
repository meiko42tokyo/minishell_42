#include "shell.h"

int	isbuiltin(t_cmd *c)
{
	// Temporary always return false.
	// TODO: Should be judged by type of command
	if (c->content)
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
		// execvp
		// TODO: Should change into our own functions
		printf("accepted command %s in pid %d!\n", c->content, getpid());
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
		printf("node:%s, %c\n", c->content, c->op); 
		c = c->next;
	}
}

int	main() {
	// test data
	char *content1 = "echo aaa";
	char *content2 = "sleep 10";
	char *content3 = "echo bbb";
	t_cmd *head;	
	t_cmd *new1;
	t_cmd *new2;
	head = ft_cmdnew(content1, 124);
	new1 = ft_cmdnew(content2, 124);
	new2 = ft_cmdnew(content3, 0);
	ft_cmdadd_back(&head, new1);
	ft_cmdadd_back(&head, new2);
	
	run_list(head);

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
