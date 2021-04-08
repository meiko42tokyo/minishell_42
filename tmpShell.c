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

t_cmd	*do_pipeline(t_cmd *c)
{
	int	haspipe;
	int	lastpipe[2];

	haspipe = 0;
	lastpipe[0] = -1;
	lastpipe[1] = -1;
	while (c)
	{
		//c->pid = start_command(c, ispipe(c), haspipe, lastpipe);
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
