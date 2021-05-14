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

	write(1, &c, 1);
	c = (char)c_int;
	tail = ft_strdup(&c);
	tail[1] = '\0';
	if (line == NULL)
		return (tail);
	ret = ft_strjoin(line, tail);
	free(line);
	line = NULL;
	return (ret);	
}

int	main()
{
	struct termios	term;
	int		c;
	char		*line;

	line = NULL;
	set_termcap(&term);
	// store standard input when enter key pressed
	while (1) {
		c = 0;
		read(0, &c, sizeof(c));
		//printf("c:%d\n", c);
		if (c == '\n')
		{
			printf("%s\n", line);
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
			line = make_line(line, c); // should store and print
		}
	}
	write(1, "\n", 1);
	reset_termcap(&term);
	return (0);
}
