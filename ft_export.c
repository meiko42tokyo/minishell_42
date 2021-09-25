#include "shell.h"

void	print_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

	tmp = (t_env *)malloc(sizeof(t_env));
	i = 0;
	while (cp_name[i])
	{
		tmp = env;
		while (tmp)
		{
			if ((ft_strcmp(cp_name[i], tmp->name) == 0) && \
					ft_strcmp(cp_name[i], "_") != 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(tmp->name, 1);
				if (tmp->value)
					put_value(tmp);
				ft_putstr_fd("\n", 1);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return ;
}

static void	put_error(char *command)
{
	ft_putstr_fd("export `", 2);
	ft_putstr_fd(command, 2);
	ft_error_str("': not a valid identifier");
}

int	ft_export(char **command, t_env *env)
{
	char		*ptr;
	char		*cd_name;
	int			sp;
	t_env		*tmp;
	t_env		*start;
	int			i;

	sp = 0;
	i = -1;
	if (command[0] == NULL)
		return (export_env(env));
	start = env;
	while (command[i])
	{
		i++;
		tmp = (t_env *)malloc(sizeof(t_env));
		ptr = ft_strchr(command[i], '=');
		if (ptr)
		{
			sp = ptr - command[i];
			if (sp == 0)
			{
				put_error(command[i]);
				env_free(tmp);
				return (1);
			}
			else
			{
				cd_name = ft_strndup(command[i], sp);
				while (env)
				{
					if (ft_strcmp(cd_name, env->name) == 0)
					{
						if (sp == (int)ft_strlen(command[i]))
						{
							env->value = ft_strdup("");
							if (command[i + 1])
								ft_export(&command[i + 1], env);
						}
						else
							env->value = ft_strdup(&command[i][sp + 1]);
						continue ;
					}
					env = env->next;
				}
			}
			tmp->name = ft_strndup(command[i], sp);
			if (sp == (int)ft_strlen(command[i]))
			{
				tmp->value = ft_strdup("");
				ft_envadd_back(&start, tmp);
				if (command[i + 1])
					ft_export(&command[i + 1], env);
				continue ;
			}
			else
				tmp->value = ft_strdup(&command[i][sp + 1]);
			ft_envadd_back(&start, tmp);
		}
		else
		{
			tmp->name = ft_strdup(command[i]);
			ft_envadd_back(&start, tmp);
		}
	}
	return (0);
}
