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

static void	put_space(char **command, int i)
{
	int	start;

	start = i;
	while (command[i])
	{
		if (i > start)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(command[i++], 1);
	}
}

static void	dup_pipe(int in, int out)
{
	if (in != -1)
		dup2(in, 0);
	if (out != -1)
		dup2(out, 1);
}

int	ft_echo(char **command)
{
	int		count;
	int		in;
	int		out;
	int		i;
	char	**n_command;

	in = -1;
	out = -1;
	if (command[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i = 0;
	while (command[i])
		i++;
	n_command = (char **)malloc(sizeof(char *) * (i + 1));
	if (!n_command)
		return (0);
	i = 0;
	while (command[i])
	{
		n_command[i] = ft_strdup(command[i]);
		i++;
	}
	n_command[i] = NULL;
	if (include_redir(command) > 0)
		n_command = ft_redirect(n_command, &in, &out);
	count = count_n(n_command);
	if (count > 1)
	{
		put_space(n_command, count);
	}
	else if (count == -1)
		return (0);
	else
	{
		put_space(n_command, 1);
		ft_putstr_fd("\n", 1);
	}
	dup_pipe(in, out);
	return_free(n_command);
	return (0);
}
