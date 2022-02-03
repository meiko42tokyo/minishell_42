#include "shell.h"

t_shell	*g_shell;

int	main(int argc, char **argv)
{
	t_cmd	*head;
	t_env	*env;
	int		ret;

	argc = 1;
	argv = NULL;
	head = NULL;
	g_shell = malloc(sizeof(t_shell));
	ft_bzero(g_shell, sizeof(t_shell));
	init_termcap();
	g_shell->status = 0;
	g_shell->line = NULL;
	g_shell->dhead = NULL;
	g_shell->cur_node = NULL;
	g_shell->save_heredoc = NULL;
	env = init_env();
	while (1)
	{
		g_shell->heredoc_fd[0] = -1;
		g_shell->heredoc_fd[1] = -1;
		signal(SIGINT, (void *)signal_handler);
		signal(SIGQUIT, (void *)signal_handler);
		ret = 0;
		ft_putstr_fd("minishell> ", 0);
		while (ret == 0)
		{
			ret = get_line();
		}
		if (ret == 1)
			break ;
		if (g_shell->cur_node != NULL && ft_strlen(g_shell->line) == 0 \
				&& g_shell->cur_node->data == NULL)
			continue ;
		if (g_shell->cur_node != NULL && \
				syntax_error(&g_shell->cur_node->data))
			continue ;
		if (g_shell->cur_node != NULL)
		{	
			head = make_cmdlist(g_shell->cur_node->data, env);
			free(g_shell->line);
			g_shell->line = NULL;
		}
		if (g_shell->cur_node != NULL && head != NULL \
				&& ft_argv_len(head) != 0)
			run_list(head, env);
		free_cmdlist(&head);
	}
	reset_termcap();
	ft_free_linehead(&g_shell->dhead);
	env_all_free(env);
	return (0);
}
