#include "shell.h"

char	*history_out(t_line **cur_node, int c)
{
	t_line	*node;
	char	*line;

	if (*cur_node == NULL)
		return (NULL);
	node = *cur_node;
	if (c == AR_U)
	{
		if (node->prev != NULL)
			(*cur_node) = node->prev;
		else
			return (NULL);
	}
	else if (c == AR_D)
	{
		if (node->next != NULL)
			(*cur_node) = node->next;
		else
			return (NULL);
	}
	tputs(tgetstr("cr", 0), 1, ft_putchar);
	tputs(tgetstr("ce", 0), 1, ft_putchar);
	write(1, (*cur_node)->data, ft_strlen((*cur_node)->data));
	line = ft_strdup((*cur_node)->data);
	return (line);
}

int	update_and_make_newnode(t_line **head, t_line **cur_node, char *line)
{
	*cur_node = ft_linenew(line);
	if (!*cur_node)
		return (-1);
	ft_lineadd_back(head, *cur_node);
	return (0);
}

int	update_and_make_empty_node(void)
{
	g_shell->cur_node = ft_linenew("");
	if (!g_shell->cur_node)
		return (-1);
	ft_lineadd_back(&g_shell->dhead, g_shell->cur_node);
	return (0);
}

int	new_line(void)
{
	if (g_shell->line == NULL)
	{
		if (g_shell->cur_node == NULL)
			return (0);
		if (ft_strlen(ft_get_latestdata(&g_shell->dhead)) \
				!= 0 && update_and_make_empty_node() != 0)
			return (-1);
		return (0);
	}
	if (g_shell->cur_node == NULL || \
			ft_strlen(ft_get_latestdata(&g_shell->dhead)) != 0)
	{
		if (update_and_make_newnode(&g_shell->dhead, \
					&g_shell->cur_node, g_shell->line) != 0)
			return (-1);
	}
	else if (ft_strlen(ft_get_latestdata(&g_shell->dhead)) == 0)
		ft_change_latestline(&g_shell->dhead, g_shell->line);
	else
	{
		free(g_shell->line);
		g_shell->line = NULL;
		return (-1);
	}
	return (0);
}
