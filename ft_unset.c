#include "shell.h"

void	ft_env_unset(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*pre;

	if (env == NULL || name == NULL)
		return ;
	tmp = *env;
	pre = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
		{
			if (pre)
				pre->next = tmp->next;
			else
				*env = tmp->next;
				env_free(tmp);
			return ;
		}
		pre = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(char **command, t_env *env)
{
	if (!command[1])
		return (0);
	while (env)
	{
		if (ft_strncmp(command[1], env->name, ft_strlen(env->name)) == 0)
		{
			if (ft_strncmp(command[1], env->name, ft_strlen(command[1])) == 0)
			{
				ft_env_unset(&env, env->name);
				return (0);
			}
			else
			{
				ft_putstr_fd("unset '", 2);
				ft_putstr_fd(command[1], 2);
				ft_error_str("': not a valid identifier");
			}
		}
		env = env->next;
	}
	//あてはまらない場合、unset: `入力コマンド': not a valid identifier
	//の表示必要
	return (0);
}
