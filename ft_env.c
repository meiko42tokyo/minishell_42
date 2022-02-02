#include "shell.h"

static void	put_error(char *command)
{
	ft_putstr_fd("env :", 2);
	ft_putstr_fd(command, 2);
	ft_error_str(": iNo such file or directory");
}

static int	judge_error(char **command)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (command[i])
	{
		t = ft_strcmp("env", command[i]);
		if (t != 0)
		{
			put_error(command[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_env(t_env *env, char **command)
{
	int	i;

	i = 0;
	if (command[1])
		i = judge_error(command);
	if (i == -1)
		return (127);
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	return (0);
}
