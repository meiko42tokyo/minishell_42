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
	signal(SIGINT, (void*)signal_handler);
	signal(SIGQUIT, (void*)signal_handler);
	env = init_env();
	while (1) {
		ret = 0;
		ft_putstr_fd("minishell> ", 0);
		while (ret == 0)
		{
			ret = get_line(line, &line_head, &cur_node);
		}
		//ft_print_linelist(&line_head, &cur_node);
		if (ret == 1)
			break;
		if (cur_node != NULL && ft_strlen(line) == 0 && cur_node->data == NULL)
			continue ;
		if (cur_node != NULL && syntax_error(&cur_node->data))
			continue ;
		if (cur_node != NULL) 
		{	
			head = make_cmdlist(cur_node->data, env);
			free(line);
			line = NULL;
		}
		if (cur_node != NULL && head != NULL && ft_argv_len(head) != 0)
			run_list(head, env);
		free_cmdlist(&head);
	}
	reset_termcap();
	ft_free_linehead(&line_head);
	env_all_free(env);
	return (0);
}
