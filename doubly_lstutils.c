#include "shell.h"

t_line	*ft_linenew(char *data)
{
	t_line	*node;

	node = (t_line*)malloc(sizeof(t_line*));
	if (node == NULL)
		return (NULL);
	node->data = ft_strdup(data);
	node->next = NULL;
	node->prev = NULL;	
	return (node);
}

void	ft_lineadd_back(t_line **head, t_line *new)
{
	t_line	*node;

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
			new->prev = node;
			node->next = new;
			break;
		}
		node = node->next;
	}
	return ;
}
/*
void	ft_free_linehead(t_line)
{
	
}*/
