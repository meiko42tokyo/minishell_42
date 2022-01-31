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

void	ft_env_unset(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*bigin;

	if (*env == NULL || name == NULL)
		return ;
	bigin = *env;
	while (*env && (*env)->next)
	{
		if (ft_strcmp((*env)->next->name, name) == 0)
		{
			tmp = (*env)->next;
			(*env)->next = (*env)->next->next;
			ft_env_lstdelone(tmp);
		}
		else
			*env = (*env)->next;
	}
	*env = bigin;
	if (ft_strcmp((*env)->name, name) == 0)
	{
		bigin = (*env)->next;
		ft_env_lstdelone(*env);
		*env = bigin;
	}
}

int	command_er_check(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!ft_isalpha(command[i]) && command[i] != '=')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_unset(char **command, t_env *env)
{
	int	error;
	int	re_error;
	int	i;
	t_env	*tmp;

	tmp = env;
	if (!command[1] || env == NULL)
		return (0);
	i = 1;
	re_error = 0;
	//_から始まるnameの処理
	while (command[i])
	{
		error = command_er_check(command[i]);
	//数字、=, /などのエラー処理をいれる
		ft_env_unset(&env, command[i]);
		if (error == -1)
		{
			re_error += error;
			ft_putstr_fd("unset `", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		env = tmp;
		i++;
	}
	if (re_error < 0)
		return (1);
	return (0);
}
