#include "shell.h"


int	main(int argc, char **argv) 
{
	char		*line;
	t_cmd		*head;
	

	argc = 1;
	argv = NULL;
	line = NULL;
	head = NULL;
	signal(SIGINT, SIG_IGN);
	while (1) {
		ft_putstr_fd("> ", 0);
		get_next_line(0, &line);
		head = make_cmdlist(line);
		free(line);
		line = NULL;
		signal(SIGINT, SIG_DFL);
		if (head != NULL)
			run_list(head);
	}
	return (0);
}
