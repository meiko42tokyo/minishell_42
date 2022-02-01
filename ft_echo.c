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

int	include_redir(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0 || \
				ft_strcmp(command[i], ">>") == 0 \
				|| ft_strcmp(command[i], "<") == 0)
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

int	ft_echo(char **command)
{
	int		count;
	//char	**n_command;

	if (command[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	//while (command[i])
	//	i++;
	//n_command = (char **)malloc(sizeof(char *) * (i + 1));
	//if (!n_command)
	//	return (0);
	//i = 0;
	//while (command[i])
	//{
	//	n_command[i] = ft_strdup(command[i]);
	//	i++;
	//}
	//n_command[i] = NULL;
	count = count_n(command);
	if (count > 1)
	{
		put_space(command, count);
	}
	else if (count == -1)
		return (0);
	else
	{
		put_space(command, 1);
		ft_putstr_fd("\n", 1);
	}
	//return_free(n_command);
	return (0);
}
