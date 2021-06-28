#include "shell.h"

int	main(int argc, char **argv) 
{
	char		*line;
	t_cmd		*head;
	t_env	*env;
	
	argc = 1;
	argv = NULL;
	line = NULL;
	head = NULL;
	signal(SIGINT, SIG_IGN);
	env = init_env();
	while (1) {
		ft_putstr_fd("> ", 0);
		get_next_line(0, &line);
		head = make_cmdlist(line, env);
		free(line);
		line = NULL;
		signal(SIGINT, SIG_DFL);
		if (head != NULL)
			run_list(head, env);
	}
	return (0);
}
