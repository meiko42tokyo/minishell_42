#include "shell.h"

t_shell	g_shell;

int	main(int argc, char **argv)
{
	char	*line;
	t_cmd	*head;
	t_env	*env;

	//leak_detect_init();
	argc = 1;
	argv = NULL;
	line = NULL;
	head = NULL;
	g_shell.status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	env = init_env();
	while (1) {
		ft_putstr_fd("minishell> ", 0);
		get_next_line(0, &line);
		if (syntax_error(&line))
			continue ;
		head = make_cmdlist(line, env);
		free(line);
		line = NULL;
		if (head != NULL && ft_argv_len(head) != 0)
			run_list(head, env);
		free_cmdlist(&head);
		//leak_detect_check();
	}
	env_all_free(env);
	return (0);
}
