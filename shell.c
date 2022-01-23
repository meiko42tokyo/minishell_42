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
		if (ret == 1)
			break;

		printf("cur_node:%c\n",*cur_node->data);
		if (cur_node && syntax_error(&cur_node->data))
			continue ;
		//printf("cur_node:%s, len:%zu\n", cur_node->data, ft_strlen(cur_node->data));
		head = make_cmdlist(cur_node->data, env);
		free(line);
		line = NULL;
		signal(SIGINT, SIG_DFL);
		if (cur_node && head != NULL && ft_argv_len(head) != 0)
			run_list(head, env);
		free_cmdlist(&head);
		//leak_detect_check();
	}
	reset_termcap();
	ft_free_linehead(&line_head);
	env_all_free(env);
	return (0);
}
