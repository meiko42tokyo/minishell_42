#include "shell.h"

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if(*env == NULL)
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
			break;
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
}

t_env	*init_env()
{
	t_env		*env;
	t_env		*tmp;
	extern char	**environ;
	int			i;
	int			start;

	env = NULL;
	i = 0;
	while(environ[i])
	{
		if(!(tmp = (t_env*)malloc(sizeof(t_env))))
		{
			ft_error_str("malloc failure", errno);
			return (NULL);
		}
		start = ft_strchr(environ[i], '=') - environ[i];
		tmp->name = ft_strndup(environ[i], start);
		tmp->value = ft_strdup(&environ[i][start + 1]);
		tmp->next = NULL;
		ft_envadd_back(&env, tmp);
		i++;
	}
	return (env);
}
