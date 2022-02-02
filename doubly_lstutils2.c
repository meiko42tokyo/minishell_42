#include "shell.h"

t_line	*ft_linenew(char *data)
{
	t_line	*node;

	node = (t_line *)malloc(sizeof(t_line));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->prev = NULL;
	node->data = ft_strdup(data);
	return (node);
}
