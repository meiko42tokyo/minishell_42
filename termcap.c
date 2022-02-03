#include "shell.h"

static int	g_judge(int c)
{
	if (g_shell->cur_node == NULL)
	{
		free(g_shell->line);
		g_shell->line = NULL;
		return (0);
	}
	if (c == AR_U && ft_strlen(g_shell->cur_node->data) != 0 \
			&& ft_strlen(ft_get_latestdata(&g_shell->dhead)) \
			!= 0 && g_shell->line == NULL)
	{
		if (update_and_make_empty_node() != 0)
			return (-1);
	}
	if (g_shell->line != NULL)
	{	
		free(g_shell->line);
		g_shell->line = NULL;
	}
	g_shell->line = history_out(&g_shell->cur_node, c);
	return (1);
}

static int	c_judge(int c)
{
	int	re;

	re = 0;
	if (c == AR_U || c == AR_D)
	{
		re = g_judge(c);
		if (re == 0 || re == -1)
			return (re);
	}
	else if (c == EOF_KEY && g_shell->line == NULL)
	{
		write(1, "exit", 4);
		return (1);
	}
	else if (ft_isprint(c))
		g_shell->line = make_line(g_shell->line, c);
	return (2);
}

int	get_line(void)
{
	int	c;
	int	re;
	int	his_depth;

	his_depth = 0;
	while (1)
	{
		c = 0;
		re = 2;
		read(0, &c, sizeof(c));
		if (c == '\n')
		{
			if (new_line() != 0)
				return (-1);
			break ;
		}
		re = c_judge(c);
		if (re != 2)
			return (re);
	}
	write(1, "\n", 1);
	free(g_shell->line);
	g_shell->line = NULL;
	return (42);
}

void	ft_print_linelist(t_line **head, t_line **cur_node)
{
	t_line	*tmp;
	int		i;

	tmp = *head;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp((*cur_node)->data, tmp->data, \
					ft_strlen((*cur_node)->data)))
		{
			ft_putstr_fd(" <-- cur_node", 1);
		}
		ft_putstr_fd("\n", 1);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
		i++;
	}
	return ;
}
