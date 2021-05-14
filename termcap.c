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

// get input of key
int	main()
{
	struct termios	term;
	int		c;

	set_termcap(&term);
	// store standard input when enter key pressed
	while (1) {
		read(0, &c, sizeof(c));
		if (c == AR_U)
			printf("AR_U\n");
		if (c == AR_D)
			printf("AR_D\n");
		if (c == EOF_KEY)
			printf("EOF\n");
		c = 0;
			// store data to doubly linked list
	}
	write(1, "\n", 1);
	reset_termcap(&term);
	return (0);
}
