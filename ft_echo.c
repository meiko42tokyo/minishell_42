#include "shell.h"

static int	count_n(char **command)
{
	int	i;
	int	t;

	i = 1;
	t = 2;
	//todo -n -nが何回繰り返されているか
	while (ft_strncmp(command[i], "-n", 2) == 0)
	{
		//-nnnnが何回繰り返されているか
		while (command[i][t])
		{
			if (command[i][t] != 'n')
			{
				return (i - 1);
			}
			t++;
		}
		i++;
	}
	return (i);
}

int	ft_echo(char **command)
{
	int	count;
	int	i;

	if ((count = count_n(command)) > 1)
	{
		i = count;
		while(command[i])
		{
			if (i > count)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(command[i++], 1);
		}
	}
	else
	{
		i = 1;
		while(command[i])
		{
			if (i > 1)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(command[i++], 1);
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
