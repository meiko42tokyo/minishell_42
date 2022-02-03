#include "shell.h"

t_shell	*g_shell;

static void	init_g(t_shell *shell)
{
	g_shell = shell;
	g_shell->status = 0;
	g_shell->line = NULL;
	g_shell->dhead = NULL;
	g_shell->cur_node = NULL;
	return ;
}

static void	make_command_run(t_env *env)
{
	t_cmd	*head;

	head = NULL;
	if (g_shell->cur_node != NULL && ft_strlen(g_shell->line) == 0 \
			&& g_shell->cur_node->data == NULL)
		return ;
	if (g_shell->cur_node != NULL && \
			syntax_error(&g_shell->cur_node->data))
		return ;
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
	return ;
}

static void	ret_set(int *ret)
{
	*ret = 0;
	ft_putstr_fd("minishell> ", 0);
	while (*ret == 0)
		*ret = get_line();
	return ;
}

int	main(int argc, char **argv)
{
	t_env	*env;
	int		ret;
	t_shell	shell;

	argc = 1;
	argv = NULL;
	ft_bzero(&shell, sizeof(t_shell));
	init_g(&shell);
	init_termcap();
	env = init_env();
	while (1)
	{
		signal(SIGINT, (void *)signal_handler);
		signal(SIGQUIT, (void *)signal_handler);
		ret_set(&ret);
		if (ret == 1)
			break ;
		make_command_run(env);
	}
	reset_termcap();
	ft_free_linehead(&g_shell->dhead);
	env_all_free(env);
	return (0);
}
