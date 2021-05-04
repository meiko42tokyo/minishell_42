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
	tcsetattr(0, TCSAFLUSH, term);
	tgetent(0, getenv("TERM"));
}

void	reset_termcap(struct termios *term)
{
	term->c_lflag |= (ECHO);
	term->c_lflag |= (ICANON);
	term->c_cc[VMIN] = 0;
	term->c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, term);
	tgetent(0, getenv("TERM"));
}

// get input of key
int	main()
{
	struct termios	term;
	int		l;
	char	str[2000];
	t_line		*cmd_line;
	t_line		*head;

	set_termcap(&term);
	// store standard input when enter key pressed
	tputs(tgetstr("sc", 0), 1, ft_putchar);
	while (1) {
		l = read(0, (void *)str, 100);
		if (!strcmp(str, "\e[D"))// right
		{
			tputs(tgetstr("le", 0), 1, ft_putchar);
		}
		if (!strcmp(str, "\e[C"))// left
		{
			tputs(tgetstr("nd", 0), 1, ft_putchar);
		}
		if (!strcmp(str, "\n"))
		{
			// store data to doubly linked list
			printf("str:%s", str);
			cmd_line = ft_linenew(str);
			ft_lineadd_back(&head, cmd_line); 
			// dubug
			cmd_line = head;
			int	i;
			i = 0;
			while (cmd_line)
			{
				printf("cmd_line->data:%d:%s\n", i, cmd_line->data);
				cmd_line = cmd_line->next;
				i++;
			}
		}/*
		else
			write(1, str, l);*/
	}
	/*while (strcmp(str, "\4"))
	{
		tputs(tgetstr("sc", 0), 1, ft_putchar);
		while (strcmp(str, "\n") && strcmp(str, "\4"))
		{
			l = read(0, (void *)str, 100);
			if (!strcmp(str, "\e[D"))// right
			{
				tputs(tgetstr("le", 0), 1, ft_putchar);
			}
			if (!strcmp(str, "\e[C"))// left
			{
				tputs(tgetstr("nd", 0), 1, ft_putchar);
			}
			else
				write(1, str, l);
		}
	}*/
	write(1, "\n", 1);
	
	reset_termcap(&term);
	return (0);
}
