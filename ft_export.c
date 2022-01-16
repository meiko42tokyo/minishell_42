#include "shell.h"

static void	put_error(char *command)
{
	ft_putstr_fd("export `", 2);
	ft_putstr_fd(command, 2);
	ft_error_str("': not a valid identifier");
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
				env->value = NULL;
				env->value = ft_strdup(&command[sp + 1]);
			}
			return (0);
		}
		env = env->next;
	}
	return (1);
}

static int	export_with_value(char *command, t_env *env, char *ptr)
{
	t_env	*tmp;
	int		sp;
	int		judge_env;
	char	*cd_name;

	sp = ptr - command;
	if (sp == 0)
	{
		put_error(command);
		return (1);
	}
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

static int	export_without_value(char *command, t_env *env)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->name = ft_strdup(command);
	tmp->value = NULL;
	ft_envadd_back(&env, tmp);
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
	r_status = 0;
	error_status = 0;
	i = 0;
	while (command[i])
	{
		ptr = ft_strchr(command[i], '=');
		if (ptr)
			r_status = export_with_value(command[i], env, ptr);
		else
			r_status = export_without_value(command[i], env);
		if (r_status == 1)
			error_status = 1;
		i++;
	}
	return (error_status);
}
