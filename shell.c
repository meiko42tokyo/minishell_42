#include "shell.h"

int	main(int argc, char **argv) 
{
	char		*line;
	t_cmd		*head;
	t_env	*env;
	
	line = NULL;
	head = NULL;
	signal(SIGINT, SIG_IGN);
	env = init_env();
	while (1) {
		ft_putstr_fd("> ", 0);
		if (argc > 2 && ft_strncmp("-c", argv[1], 3) == 0)
		{
			head = make_cmdlist(argv[2]);
		}
		else
		{
			get_next_line(0, &line);
			head = make_cmdlist(line);
			free(line);
			line = NULL;
		}
		signal(SIGINT, SIG_DFL);
		if (head != NULL)
			run_list(head, env);
	}
	return (0);
}
