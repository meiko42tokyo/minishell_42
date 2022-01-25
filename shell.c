#include "shell.h"

t_shell	*g_shell;

int	main(int argc, char **argv)
{
	char	*line;
	t_cmd	*head;
	t_env	*env;
	t_line		*line_head;
	t_line		*cur_node;
	int		ret;
	t_shell		shell;

	//leak_detect_init();
	argc = 1;
	argv = NULL;
	line = NULL;
	head = NULL;
	line_head = NULL;
	cur_node = NULL;
	ft_bzero(&shell, sizeof(t_shell));
	g_shell = &shell;
	set_termcap();
	g_shell->status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	env = init_env();
	while (1) {
		ret = 0;
		ft_putstr_fd("minishell> ", 0);
		while (ret == 0)
		{
			ret = get_line(line, &line_head, &cur_node);
		}
		ft_print_linelist(&line_head, &cur_node);
		if (ret == 1)
			break;
		if (ft_strlen(line) == 0 && cur_node == NULL)
			continue ;
		if (syntax_error(&cur_node->data))
			continue ;
		head = make_cmdlist(cur_node->data, env);
		free(line);
		line = NULL;
		signal(SIGINT, SIG_DFL);
		if (head != NULL && ft_argv_len(head) != 0)
			run_list(head, env);
		free_cmdlist(&head);
		//leak_detect_check();
	}
	reset_termcap();
	ft_free_linehead(&line_head);
	env_all_free(env);
	return (0);
}
