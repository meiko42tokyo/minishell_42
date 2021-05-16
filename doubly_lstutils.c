#include "shell.h"

t_line	*ft_linenew(char *data)
{
	t_line	*node;

	node = (t_line*)malloc(sizeof(t_line));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;	
	node->data = ft_strdup(data);
	return (node);
}

int	ft_lineadd_back(t_line **head, t_line *new)
{
	t_line	*node;

	if (*head == NULL)
	{
		*head = new;
		return (0);
	}
	if (new == NULL)
		return (-1);
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
	return (0);
}

void	ft_free_linehead(t_line **head)
{
	t_line *node;

	if (*head == NULL)
		return ;
	node = *head;
	while (node)
	{
		free(node->data);
		if (node->next == NULL)
			break;
		node = node->next;
		free(node->prev);
	}
	free(node);
}
