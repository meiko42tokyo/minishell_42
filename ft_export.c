#include "shell.h"

static void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if(*env == NULL)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

int	ft_export(char **command, t_env *env)
{
	char		*cd_name;
	int			sp;
	t_env		*tmp;

	sp = ft_strchr(command[0], '=') - command[0];//=までの文字の長さをくっつける
	cd_name = ft_strndup(command[0], sp);
	while (env) 
	{
		if (ft_strncmp(cd_name, env->name, sp) == 0)//文字列がenvironのどれかと一致した場合
		{
			env->value = ft_strdup(&command[0][sp + 1]); 
			return (0);
		}
		env = env->next;
	}
	tmp = (t_env*)malloc(sizeof(t_env));
	tmp->name = ft_strndup(command[0], sp);
	tmp->value = ft_strdup(&command[0][sp + 1]);
	ft_envadd_back(&env, tmp);
	printf("add\nline[%s]\nvalue[%s]\n", tmp->name, tmp->value);
	return (0);
}
