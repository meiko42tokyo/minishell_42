#include "shell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	set_termcap()
{
	tcgetattr(0, &g_shell->term);
	tcgetattr(0, &g_shell->term_origin);
	g_shell->term.c_lflag &= ~(ECHO);
	g_shell->term.c_lflag &= ~(ICANON);
	g_shell->term.c_cc[VMIN] = 1;
	g_shell->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_shell->term);
	tgetent(0, getenv("TERM"));
}

void	reset_termcap()
{
	tcsetattr(0, TCSANOW, &g_shell->term_origin);
}

char	*make_line(char *line, int c_int)
{
	char		*ret;
	char		*tail;
	char	c;

	c = (char)c_int;
	write(1, &c, 1);
	tail = ft_strndup(&c, 1);
	if (line == NULL)
		return (tail);
	ret = ft_strjoin(line, tail);
	free(line);
	free(tail);
	line = NULL;
	tail = NULL;
	return (ret);	
}

// only up first
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

int	new_line(char *line, t_line **head, t_line **cur_node)
{
	if (line == NULL)
	{
		if (*cur_node == NULL)
			return (0);
		if (ft_strlen(ft_get_latestdata(head)) != 0 && update_and_make_newnode(head, cur_node, "") != 0)
			return (-1);
		return (0);
	}
	if (*cur_node == NULL || ft_strlen(ft_get_latestdata(head)) != 0)
	{
		if (update_and_make_newnode(head, cur_node, line) != 0)
			return (-1);
	}
	else if (ft_strlen(ft_get_latestdata(head)) == 0)
		ft_change_latestline(head, line);
	else
	{
		free(line);
		line = NULL;
		return (-1);
	}
	return (0);	
}

int	get_line(char *line, t_line **head, t_line **cur_node)
{
	int		c;
	int		his_depth;

	his_depth = 0;
	while (1) {
		c = 0;
		read(0, &c, sizeof(c));
		if (c == '\n')
		{
			if (new_line(line, head, cur_node) != 0)
				return (-1);
			break ;
		}
		if (c == AR_U || c == AR_D)
		{
			if (*cur_node == NULL)
			{
				free(line);
				line = NULL;
				return (0);
			}
			if (c == AR_U && ft_strlen((*cur_node)->data) != 0  && ft_strlen(ft_get_latestdata(head)) != 0 && line == NULL)
			{
				if (update_and_make_newnode(head, cur_node, "") != 0)
					return (-1);
			}
			if (line != NULL)
			{	
				free(line);
				line = NULL;
			}
			line = history_out(cur_node, c);
		}
		else if (c == EOF_KEY)
		{
			write(1, "exit", 4);
			return (1);
		}
		else if (ft_isprint(c))
			line = make_line(line, c);
	}
	write(1, "\n", 1);
	free(line);
	line = NULL;
	return (42);
}

void	ft_print_linelist(t_line **head, t_line **cur_node)
{
	t_line		*tmp;
	int		i;
	
	tmp = *head;
	i = 0;
	while (tmp)
	{
		//printf("node[%d]:%s\n", i, tmp->data);
		if (!ft_strncmp((*cur_node)->data, tmp->data, ft_strlen((*cur_node)->data)))
		{
			printf(" <-- cur_node");
		}
		printf("\n");
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
		i++;
	}
	return ;
}
