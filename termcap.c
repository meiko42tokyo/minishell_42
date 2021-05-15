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

// store data to doubly linked list
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
	line = NULL;
	return (ret);	
}

int	*get_line(char **line)
{
	int		c;
	t_line		*head;
	// store standard input when enter key pressed
	head = NULL;
	while (1) {
		c = 0;
		read(0, &c, sizeof(c));
		//printf("c:%d, isprint:%d\n", c, ft_isprint(c));
		if (c == '\n')
		{
			//store in doubly linked list
			ft_lineadd_back(&head, ft_linenew(*line));		
			break ;
		}
		else if (c == AR_U)
			printf("AR_U\n");
		else if (c == AR_D)
			printf("AR_D\n");
		else if (c == EOF_KEY)
			printf("EOF\n");
		else if (ft_isprint(c))
		{
			*line = make_line(*line, c);
		}
	}
	//free(*line);
	printf("%s\n", head->data);
	write(1, "\n", 1);
	return (0);
}

int	main()
{
	struct termios	term;
	char		*line;

	set_termcap(&term);
	line = NULL;
	while (1)
	{
		if (line != NULL)
			free(line);
		line = NULL;
		get_line(&line);
	}
	reset_termcap(&term);
	return (0);
}
