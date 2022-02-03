#include "shell.h"

void	put_value(t_env *tmp)
{
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(tmp->value, 1);
	ft_putstr_fd("\"", 1);
}

void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	sort_env(char **cp_name)
{
	int		i;
	int		j;

	i = 0;
	while (cp_name[i])
	{
		j = i + 1;
		while (cp_name[j])
		{
			if (ft_strcmp(cp_name[i], cp_name[j]) > 0)
				swap(&cp_name[i], &cp_name[j]);
			j++;
		}
		i++;
	}
	return (0);
}

int	dup_env(t_env *env, char **cp_name)
{
	t_env	*tmp;
	int		i;

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

int	export_env(t_env *env)
{
	char	*cp_name[100];

	dup_env(env, cp_name);
	sort_env(cp_name);
	print_env(env, cp_name);
	return (0);
}
