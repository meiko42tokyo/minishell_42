#include "shell.h"

static void	print_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

	tmp = (t_env*)malloc(sizeof(t_env));
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

	tmp = (t_env*)malloc(sizeof(t_env));
	tmp = env;
	i = 0;
	while (tmp)
	{
		cp_name[i] = ft_strdup(tmp->name);
		tmp = tmp->next;
		i++;
	}
	cp_name[i] = NULL;
	return (0);
}

static int	export_env(t_env *env)
{
	char	*cp_name[100];

	//あとでマロックの仕方要検討
	dup_env(env, cp_name);
	sort_env(cp_name);
	print_env(env, cp_name);
	return (0);
}

int	ft_export(char **command, t_env *env)
{
	char		*ptr;
	char		*cd_name;
	int			sp;
	t_env		*tmp;
	t_env		*start;

	sp = 0;
	if (command[0] == NULL)
		return (export_env(env));
	start = env;
	ptr = ft_strchr(command[0], '=');
	tmp = (t_env*)malloc(sizeof(t_env));
	if (ptr)
	{
		sp = ptr - command[0];
		if (sp == 0)
		{
			ft_putstr_fd("export `", 2);
			ft_putstr_fd(command[0], 2);
			ft_error_str("': not a valid identifier");
			env_free(tmp);
			return (0);
		}
		else
		{
			cd_name = ft_strndup(command[0], sp);
			while (env) 
			{
				if (ft_strcmp(cd_name, env->name) == 0)
				{
					if (sp == (int)ft_strlen(command[0]))//aaa=　ooのとき
					{
						env->value = ft_strdup("");
						if (command[1])
							ft_export(&command[1], env);
					}
					else
						env->value = ft_strdup(&command[0][sp + 1]);
					return (0);
				}
				env = env->next;
			}
		}
		tmp->name = ft_strndup(command[0], sp);
		if (sp == (int)ft_strlen(command[0]))
		{
			tmp->value = ft_strdup("");
			ft_envadd_back(&start, tmp);
			if (command[1])
				ft_export(&command[1], env);
			return (0);
		}
		else
			tmp->value = ft_strdup(&command[0][sp + 1]);
		ft_envadd_back(&start, tmp);
		return (0);
	}
	else if (command[1])
	{
		ft_putstr_fd("export `", 2);
		ft_putstr_fd(command[1], 2);
		ft_error_str("': not a valid identifier");
		
	}
	tmp->name = ft_strdup(command[0]);
	ft_envadd_back(&start, tmp);
	return (0);
}
