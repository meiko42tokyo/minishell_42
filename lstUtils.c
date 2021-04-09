#include "shell.h"

t_cmd	*ft_cmdnew(char *content, int op)
{
	t_cmd	*node;

	node = (t_cmd*)malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->content = content;
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
		return;
	}
	node = *head;
	while (node)
	{
		if (node->next == NULL)
		{
			node->next = new;
			break;
		}
		node=node->next;
	}
}
