#include "shell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b", 1);
		ft_putstr_fd("\nminishell> ", 0);
		free(g_shell->line);
		g_shell->line = NULL;
	}
}

void	signal_handler_child(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("^C\n", 1);
	}
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("^\\Quit: 3\n", 1);
	}
	signal(SIGINT, signal_handler);
}
