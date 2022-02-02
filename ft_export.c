#include "shell.h"

static int	put_error(char *command)
{
	ft_putstr_fd("export `", 2);
	ft_putstr_fd(command, 2);
	ft_error_str("': not a valid identifier");
	return (1);
}

static int	is_env(char *cd_name, char *command, t_env *env, int sp)
{
	while (env)
	{
		if (ft_strcmp(cd_name, env->name) == 0)
		{
			if (sp == (int)ft_strlen(command))
				env->value = ft_strdup("");
			else
			{
				free(env->value);
				env->value = ft_strdup(&command[sp + 1]);
			}
			return (0);
		}
		env = env->next;
	}
	return (1);
}

static int	export_without_value(char *command, t_env *env)
{
	t_env	*tmp;
	int		check;

	check = 0;
	tmp = env;
	while (env)
	{
		if (ft_strcmp(command, env->name) == 0)
		{
			check = 1;
			break ;
		}
		env = env->next;
	}
	env = tmp;
	if (check == 0)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		tmp->name = ft_strdup(command);
		tmp->value = NULL;
		ft_envadd_back(&env, tmp);
	}
	return (0);
}

static int	value_judge(char *command, t_env *env, char *ptr)
{
	t_env	*tmp;
	int		sp;
	int		judge_env;
	char	*cd_name;

	if (!ptr)
		return (export_without_value(command, env));
	sp = ptr - command;
	if (sp == 0)
		return (put_error(command));
	cd_name = ft_strndup(command, sp);
	judge_env = is_env(cd_name, command, env, sp);
	if (judge_env == 1)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		tmp->name = ft_strdup(cd_name);
		tmp->value = ft_strdup(&command[sp + 1]);
		ft_envadd_back(&env, tmp);
	}
	free(cd_name);
	return (0);
}

int	ft_export(char **command, t_env *env)
{
	char		*ptr;
	int			i;
	int			r_status;
	int			error_status;

	if (command[0] == NULL)
		return (export_env(env));
	r_status = ft_strcmp(command[0], "_");
	if (r_status == 0)
		return (ft_env_unset(&env, "_"));
	i = 0;
	while (command[i])
	{
		error_status = command_ex_check(command[i], &r_status, &i);
		if (error_status < 0)
			continue ;
		ptr = ft_strchr(command[i], '=');
		value_judge(command[i++], env, ptr);
	}
	if (r_status < 0)
		return (1);
	return (0);
}
