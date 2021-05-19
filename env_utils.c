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
//	printf("line=%s, name=%s, value=%s\n", tmp->line, tmp->name, tmp->value);
}

/*
t_env	*dup_env(t_env *env)
{
	//if (env == NULL)
	t_env	*tmp;

	while (env)
	{
		if (!(ft_strncmp(env->name, "-", 1) == 0 && env->name[1] != '\0'))
		{
			tmp = (t_env*)malloc(sizeof(t_env));
			tmp->name = env->name;
			if (env->value)
				tmp->value = env->value;
			ft_envadd_back(&tmp, tmp);
		}
		env = env->next;
	}
	return (tmp);
}
*/

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
		tmp = (t_env*)malloc(sizeof(t_env));
		if (tmp == NULL)
			return (NULL);//エラー処理追記;
		start = ft_strchr(environ[i], '=') - environ[i];
		tmp->name = ft_strndup(environ[i], start);
		tmp->value = ft_strdup(&environ[i][start + 1]);
		//printf("i=%d, line=%s, name=%s, value=%s\n", i, tmp->line, tmp->name, tmp->value);
		ft_envadd_back(&env, tmp);
		//env_free(tmp);
		i++;
	}
//	printf("line=%s, name=%s, value=%s\n", env->line, env->name, env->value);
	return (env);
}
