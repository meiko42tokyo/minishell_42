#include "shell.h"

static void	print_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

	if (!(tmp = (t_env*)malloc(sizeof(t_env))))
		return ;
	i = 0;
	while(cp_name[i])
	{
		tmp = env;
		while (tmp)
		{
			//１回目のexportは_=出る問題
			if ((ft_strcmp(cp_name[i], tmp->name) == 0) &&\
					ft_strcmp(cp_name[i], "_") != 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->name, 1);
				if (tmp->value)
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(tmp->value, 1);
					ft_putstr_fd("\"", 1);
				}
				ft_putstr_fd("\n", 1);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return ;
}

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static int sort_env(char **cp_name)
{
	int		i;
	int		j;

	i = 0;
	while(cp_name[i])
	{
		j = i + 1;
		while(cp_name[j])
		{
			if(ft_strcmp(cp_name[i], cp_name[j]) > 0)
				swap(&cp_name[i], &cp_name[j]);
			j++;
		}
		i++;
	}
	return (0);
}

static int	dup_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

	if (!(tmp = (t_env*)malloc(sizeof(t_env))))
		return (ft_error_str("malloc failure", errno));
	tmp = env;
	i = 0;
	while (tmp)
	{
		cp_name[i] = ft_strdup(tmp->name);
		tmp = tmp->next;
		i++;
	}
	cp_name[i] = NULL;
	//free(tmp);
	return (0);
}

static int	export_env(t_env *env)
{
	char	*cp_name[100];

	//あとでマロックの仕方要検討
	if (!env)
		return (1);
	dup_env(env, cp_name);
	sort_env(cp_name);
	print_env(env, cp_name);
	return (0);
}

int	env_replace(char *cd_name, int sp, char *command, t_env *env)
{
	while (env) 
	{
		if (ft_strcmp(cd_name, env->name) == 0)
		{
			if (sp == (int)ft_strlen(command))//aaa=　ooのとき
				env->value = ft_strdup("");
			else
				env->value = ft_strdup(&command[sp + 1]);
			return (1) ;
		}
		env = env->next;
	}
	return (0);
}


int	ft_export(char **command, t_env *env)
{
	char		*ptr;
	char		*cd_name;
	int			sp;
	int			i;
	int			env_re;
	t_env		*tmp;
	//t_env		*start;

	sp = 0;
	if (command[0] == NULL)
		return (export_env(env));
	i = 0;
	//if (!(start = (t_env*)malloc(sizeof(t_env))))
	//	(ft_error_str("malloc failure", errno));
	//start = env;
	while (command[i])
	{
		if (!(tmp = (t_env*)malloc(sizeof(t_env))))
			(ft_error_str("malloc failure", errno));
		if (i == 7)
			exit (0);
		printf("command:%s\n", command[i]);
		ptr = ft_strchr(command[i], '=');
		if (ptr)
		{
			sp = ptr - command[i];
			if (sp == 0)
			{
				ft_putstr_fd("minishell: export `", 2);
				ft_putstr_fd(command[i], 2);
				return (ft_error_str("': not a valid identifier", 1));
				//env_free(tmp);
			}
			else
			{
				cd_name = ft_strndup(command[i], sp);
				env_re = env_replace(cd_name, sp, command[i], env);
				if (env_re == 0)
				{
					tmp->name = ft_strndup(command[i], sp);
					if (sp == (int)ft_strlen(command[i]))
						tmp->value = ft_strdup("");
					else
						tmp->value = ft_strdup(&command[i][sp + 1]);
				}
				else
					tmp = NULL;
			}
		}
		else
		{
			tmp->name = ft_strdup(command[i]);
			tmp->value = NULL;
		}
		if (tmp)
			ft_envadd_back(&env, tmp);
		i++;
	}
	return (0);
}
