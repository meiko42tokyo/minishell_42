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
			if (ft_strncmp(cp_name[i], tmp->name, ft_strlen(tmp->name)) == 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->name, 1);
				if (tmp->value)
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(tmp->value, 1);
					ft_putstr_fd("\"\n", 1);
				}
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return ;
}

static int sort_env(char **cp_name)
{
	printf("%s\n", cp_name[10]);
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
	char		*cd_name;
	int			sp;
	t_env		*tmp;
	t_env		*start;

	sp = 0;
	if (command[0] == NULL)
		return (export_env(env));
	start = env;
	if (ft_strchr(command[0], '='))
	{
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
		ft_envadd_back(&start, tmp);
	}
	else
	{
		tmp = (t_env*)malloc(sizeof(t_env));
		tmp->name = ft_strndup(command[0], sp);
		ft_envadd_back(&start, tmp);
	}
	return (0);
}
