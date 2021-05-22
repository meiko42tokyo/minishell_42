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

int	get_line(char *line, t_line **head, t_line **cur_node)
{
	int		c;
	int		his_depth;

	his_depth = 0;
	while (1) {
		c = 0;
		read(0, &c, sizeof(c));
		// 改行の時の処理
		//もしlineに中身があるのなら、cur_nodeに入れたい
		//しかし、cur_nodeがnullの可能性もある
		//なので問答無用で作成するようにしたい
		//でも、たとえばもし一個前に空のcur_nodeがあるのならそこに代入したい
		// cur_node == NULL -> とりあえず作る
		// cur_node != NULL && cur_node->data == 0 -> 一個前に入れたい
		// cur_node != NULL && cur_node->data != 0 -> 新しいnode作 
		if (c == '\n')
		{
			if (line != NULL)
			{
				if (*cur_node == NULL)
				{
					*cur_node = ft_linenew(line);
					if (!*cur_node)
						return (-1);
					ft_lineadd_back(head, *cur_node);
					break ;
				}
				if (ft_strlen(ft_get_latestdata(head)) != 0)
				{
					*cur_node = ft_linenew(line);
					if (!*cur_node)
						return (-1);
					ft_lineadd_back(head, *cur_node);
				}
				else if (ft_strlen(ft_get_latestdata(head)) == 0)
				{
					ft_change_latestline(head, line);
				}
				else
				{
					free(line);
					line = NULL;
					return (0);
				}
				//printf("cur_node:%s\n", (*cur_node)->data);
			}
			break ;
		}
		else if (c == AR_U || c == AR_D)
		{
			/*if (line != NULL)
			{
				if (ft_lineadd_back(head, ft_linenew(line)) == -1)
					return (-1);
			}*/
			if (*cur_node == NULL)
			{
				free(line);
				line = NULL;
				return (0);
			}
			if (c == AR_U && ft_strlen((*cur_node)->data) != 0  && ft_strlen(ft_get_latestdata(head)) != 0 && line == NULL)
			{
				line = ft_strndup("", 1);
				*cur_node = ft_linenew(line);
				if (!(*cur_node))
					return (-1);
				ft_lineadd_back(head, *cur_node);
			}
			//printf("cur_node:%s\n", (*cur_node)->data);
			if (line != NULL)
			{
				free(line);
				line = NULL;
			}
			line = history_out(cur_node, c);// assign ret to line?
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
	t_line		*cur_node;
	int		ret;

	head = NULL;
	set_termcap(&term);
	line = NULL;
	cur_node = NULL;
	while (1)
	{
		ret = get_line(line, &head, &cur_node);
		if (ret == 1)
			break;
	}
	reset_termcap(&term);
	ft_print_linelist(&head);
	ft_free_linehead(&head);
	return (0);
}
