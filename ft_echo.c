#include "shell.h"

static int	count_n(char **command)
{
	int	i;
	int	t;

	i = 1;
	t = 2;
	while (ft_strncmp(command[i], "-n", 2) == 0)
	{
		while (command[i][t])
		{
			if (command[i][t] != 'n')
			{
				return (i - 1);
			}
			t++;
		}
		i++;
		if (command[i] == NULL)
			return (-1);
	}
	return (i);
}

static int	include_redir(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0 || \
				ft_strcmp(command[i], ">>") == 0 \
				|| ft_strcmp(command[i], "<<") == 0 || \
				ft_strcmp(command[i], "<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **command)
{
	int	count;
	int	i;
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (command[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (include_redir(command) > 0)
		command = ft_redirect(command, &in, &out);
	if ((count = count_n(command)) > 1)
	{
		i = count;
		while (command[i])
		{
			if (i > count)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(command[i++], 1);
		}
	}
	else if (count == -1)
		return (0);
	else
	{
		i = 1;
		while (command[i])
		{
			if (i > 1)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(command[i++], 1);
		}
		ft_putstr_fd("\n", 1);
	}
	if (in != -1)
		dup2(in, 0);
	if (out != -1)
		dup2(out, 1);
	return (0);
}
