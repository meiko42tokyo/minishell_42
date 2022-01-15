#include "shell.h"

void	del(char *info)
{
	free(info);
}

void	ft_env_lstdelone(t_env *env, void(*del)(char *))
{
	if (env == NULL || !del)
		return ;
	del(env->name);
	del(env->value);
	free(env);
	return ;
}

void	ft_env_unset(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*pre;

	if (env == NULL || name == NULL)
		return ;
	tmp = env;
	pre = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			if (pre)
				pre->next = tmp->next;
			else
				env = tmp->next;
			ft_env_lstdelone(tmp, &del);
			break ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(char **command, t_env *env)
{
	int	error;

	error = -1;
	if (!command[1])
		return (0);
	while (env)
	{
		if (ft_strcmp(command[1], env->name) == 0)
		{
			ft_env_unset(env, env->name);
			error = 0;
			break ;
		}
		env = env->next;
	}
	if (error == -1)
	{
		ft_putstr_fd("unset `", 2);
		ft_putstr_fd(command[1], 2);
		ft_error_str("': not a valid identifier");
	}
	return (0);
}
