#include "shell.h"

t_shell	*g_shell;

int	main(int argc, char **argv)
{
	t_cmd	*head;
	t_env	*env;
	int		ret;
	t_shell		shell;

	argc = 1;
	argv = NULL;
	head = NULL;
	ft_bzero(&shell, sizeof(t_shell));
	g_shell = &shell;
	init_termcap();
	g_shell->status = 0;
	g_shell->line = NULL;
	g_shell->dhead = NULL;
	g_shell->cur_node = NULL;
	env = init_env();
	while (1) {
		signal(SIGINT, (void*)signal_handler);
		signal(SIGQUIT, (void*)signal_handler);
		ret = 0;
		ft_putstr_fd("minishell> ", 0);
		while (ret == 0)
		{
			ret = get_line(g_shell->line, &g_shell->dhead, &g_shell->cur_node);
		}
		//ft_print_linelist(&line_head, &cur_node);
		if (ret == 1)
			break;
		if (g_shell->cur_node != NULL && ft_strlen(g_shell->line) == 0 && g_shell->cur_node->data == NULL)
			continue ;
		if (g_shell->cur_node != NULL && syntax_error(&g_shell->cur_node->data))
			continue ;
		if (g_shell->cur_node != NULL) 
		{	
			head = make_cmdlist(g_shell->cur_node->data, env);
			free(g_shell->line);
			g_shell->line = NULL;
		}
		if (g_shell->cur_node != NULL && head != NULL && ft_argv_len(head) != 0)
			run_list(head, env);
		free_cmdlist(&head);
	}
	reset_termcap();
	ft_free_linehead(&g_shell->dhead);
	env_all_free(env);
	return (0);
}
