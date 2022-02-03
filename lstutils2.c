#include "shell.h"

t_cmd	*ft_cmdnew(char *argv[], int op)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->argv = argv;
	node->pid = -1;
	node->op = op;
	return (node);
}

void	ft_cmdadd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*node;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node)
	{
		if (node->next == NULL)
		{
			node->next = new;
			break ;
		}
		node = node->next;
	}
	node->next->next = NULL;
	return ;
}

int	ft_argv_len(t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->argv[len])
	{
		len++;
	}
	return (len);
}

int	ft_print_cmdsize(t_cmd **head)
{
	t_cmd	*node;
	int		index;

	node = *head;
	index = 0;
	while (node)
	{
		index++;
		if (node->next == NULL)
		{
			break ;
		}
		node = node->next;
	}
	return (index);
}

int	check_argvsize(t_cmd *node)
{
	int	size;

	size = 0;
	while (node->argv[size])
		size++;
	return (size);
}
