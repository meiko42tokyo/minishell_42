#include "shell.h"

void	ft_env_lstdelone(t_env *env)
{
	if (env == NULL)
		return ;
	free(env->name);
	free(env->value);
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
			ft_env_lstdelone(tmp);
			return ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(char **command, t_env *env)
{
	int	error;
	t_env	*tmp;

	error = -1;
	tmp = env;
	if (!command[1] || env == NULL)
		return (0);
	//_から始まるnameの処理
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
	while (tmp)
	{
		printf("name:%s\n", tmp->name);
		tmp = tmp->next;
	}
	return (0);
}
