#include "shell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	set_termcap(struct termios *term)
{
	tcgetattr(0, term);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, term);
	tgetent(0, getenv("TERM"));
}

void	reset_termcap(struct termios *term)
{
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, term);
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
void	history_out(t_line **head, int *depth, int c)
{
	int	i;
	int	his_size;
	t_line	*node;

	i = 0;
	his_size = ft_get_lstsize(head);
	if (c == AR_U)
	{
		if (*depth + 1 <= his_size)
			(*depth)++;
		else
			return ;
	}
	else if (c == AR_D)
	{
		if (*depth - 1 >= 0)
			(*depth)--;
		else
			return ;
	}
	//printf("depth:%d, size:%d\n", *depth, his_size);
	node = *head;
	while (i < his_size - *depth - 1)
	{
		node = node->next;
		i++;
	}
	write(1, node->data, ft_strlen(node->data));
}

int	get_line(char *line, t_line **head)
{
	int		c;
	int		his_depth;

	his_depth = 0;
	while (1) {
		c = 0;
		read(0, &c, sizeof(c));
		if (c == '\n')
		{
			if (line != NULL)
				if (ft_lineadd_back(head, ft_linenew(line)) == -1)
					return (-1);
			break ;
		}
		else if (c == AR_U || c == AR_D)
		{
			// save depth 0	
			if (his_depth == 0 && c == AR_U)
			{
				if (line == NULL)
					line = ft_strndup("", 1);
				if (ft_lineadd_back(head, ft_linenew(line)) == -1)
					return (-1);
			}
			history_out(head, &his_depth, c);// assign ret to line?
		}
		else if (c == EOF_KEY)
		{
			printf("EOF\n");
			return (1);
		}
		else if (ft_isprint(c))
		{
			line = make_line(line, c);
		}
	}
	free(line);
	line = NULL;
	//printf("size:%d\n", ft_get_lstsize(head));
	write(1, "\n", 1);
	return (0);
}

void	ft_print_linelist(t_line **head)
{
	t_line		*tmp;
	int		i;
	tmp = *head;
	i = 0;
	while (tmp)
	{
		printf("node[%d]:%s\n", i, tmp->data);
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
		i++;
	}
	return ;
}

int	main()
{
	struct termios	term;
	char		*line;
	t_line		*head;
	int		ret;

	head = NULL;
	set_termcap(&term);
	line = NULL;
	while (1)
	{
		ret = get_line(line, &head);
		if (ret == 1)
			break;
	}
	reset_termcap(&term);
	ft_print_linelist(&head);
	ft_free_linehead(&head);
	return (0);
}
