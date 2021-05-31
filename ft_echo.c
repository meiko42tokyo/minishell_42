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

static int echo_env(char *str, t_env *env)
{
	int	sp;
	char	*tmp;
	char	*print;

	sp = ft_strchr(str, '$') - str;
	if (sp > 0)
	{
		tmp = ft_strndup(str, sp);
		ft_putstr_fd(tmp, 1);
		free(tmp);
		tmp = NULL;
	}
	tmp = ft_strdup(&str[sp + 1]);
	sp = ft_strchr(tmp, '$') - tmp;
	if (sp > 0)
		print = ft_strndup(tmp, sp);
	else
		print = ft_strdup(tmp);
	while (env)
	{
		if (ft_strcmp(print, env->name) == 0)
		{
			ft_putstr_fd(env->value, 1);
			break ;
		}
		env = env->next;
	}
	if (sp > 0)
		echo_env(&tmp[sp], env);
	return (0);
}

int	ft_echo(char **command, t_env *env)
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
			if (ft_strchr(command[i], '$'))
				echo_env(command[i], env);
			else
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
			if (ft_strchr(command[i], '$'))
				echo_env(command[i], env);
			else
				ft_putstr_fd(command[i], 1);
			i++;
		}
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
