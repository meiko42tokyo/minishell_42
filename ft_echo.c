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
//	char	*status;

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
/*
	if (print[1] == '?')
	{
		status = ft_itoa($PIPESTATUS[0]);
		ft_putstr_fd(status, 1);
	//あとで後の文字も印字できるようにする
	}
*/
	while (env)
	{
		if (ft_strcmp(print, env->name) == 0)
		{
			ft_putstr_fd(env->value, 1);
			break ;
		}
		env = env->next;
	}
	if (sp > 1)
		echo_env(&tmp[sp], env);
	return (0);
}

static int	include_redir(char **command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (ft_strcmp(command[i], ">") == 0 || ft_strcmp(command[i], ">>") == 0\
			|| ft_strcmp(command[i], "<<") == 0 || ft_strcmp(command[i], "<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(char **command, t_env *env)
{
	int	count;
	int	i;
	int	in;
	int	out;

	in = -1;
	out = -1;
	if (include_redir(command) > 0)
		command = ft_redirect(command, &in, &out);
	if ((count = count_n(command)) > 1)
	{
		i = count;
		while(command[i])
		{
			//ここ以降別関数に書き出し
			if (i > count)
				ft_putstr_fd(" ", 1);
			if (ft_strchr(command[i], '$'))
				echo_env(command[i], env);
			else
				ft_putstr_fd(command[i], 1);
			i++;
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
	if (in != -1)
		dup2(in, 0);
	if (out != -1)
		dup2(out, 1);
	return (0);
}
