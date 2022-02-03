#include "shell.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	init_termcap(void)
{
	tcgetattr(0, &g_shell->term);
	tcgetattr(0, &g_shell->term_origin);
	set_termcap();
}

void	set_termcap(void)
{
	g_shell->term.c_lflag &= ~(ECHO);
	g_shell->term.c_lflag &= ~(ICANON);
	g_shell->term.c_cc[VMIN] = 1;
	g_shell->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &g_shell->term);
	tgetent(0, getenv("TERM"));
}

void	reset_termcap(void)
{
	tcsetattr(0, TCSANOW, &g_shell->term_origin);
}

char	*make_line(char *line, int c_int)
{
	char	*ret;
	char	*tail;
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
