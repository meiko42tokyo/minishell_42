#include "shell.h"

t_shell	g_shell;

int	main(int argc, char **argv) 
{
	struct termios	term;
	char		*line;
	t_cmd		*head;
	t_line		*line_head;
	t_line		*cur_node;
	int		ret;
	t_env		*env;
	
	argc = 1;
	argv = NULL;
	line = NULL;
	head = NULL;
	line_head = NULL;
	cur_node = NULL;
	set_termcap(&term);
	g_shell.status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	env = init_env();
	//printf("%s, %s\n", env->name, env->value);
	while (1) {
		ret = 0;
		ft_putstr_fd("minishell> ", 0);
		while (ret == 0)
		{
			ret = get_line(line, &line_head, &cur_node);
		}
		if (ret == 1)
			break;
		//get_next_line(0, &input); // TODO: if fail in GNL
		// save input to doubly linked list
		head = make_cmdlist(cur_node->data, env);
		free(line);
		line = NULL;
		signal(SIGINT, SIG_DFL);
		if (head != NULL && ft_argv_len(head))
			run_list(head, env);
		free_cmdlist(&head);
	}
	reset_termcap(&term);
	ft_free_linehead(&line_head);
	env_all_free(env);
	return (0);
}
