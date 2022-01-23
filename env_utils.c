#include "shell.h"

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp->next = new;
			tmp = tmp->next;
			tmp->next = NULL;
			break ;
		}
		tmp = tmp->next;
	}
}

void	env_free(t_env *env)
{
	free(env->name);
	env->name = NULL;
	free(env->value);
	env->value = NULL;
	free(env);
	env = NULL;
}

void	env_all_free(t_env *env)
{
	t_env *node;

	while (env)
	{
		node = env->next;
		env_free(env);
		env = node;
	}
}

t_env	*init_env(void)
{
	t_env		*env;
	t_env		*tmp;
	extern char	**environ;
	int			i;
	int			start;

	env = NULL;
	i = 0;
	while (environ[i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			return (NULL);//エラー処理追記;
		start = ft_strchr(environ[i], '=') - environ[i];
		tmp->name = ft_strndup(environ[i], start);
		tmp->value = ft_strdup(&environ[i][start + 1]);
		tmp->next = NULL;
		ft_envadd_back(&env, tmp);
		//env_free(tmp);
		i++;
	}
	return (env);
}
