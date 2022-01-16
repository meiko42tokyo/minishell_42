#include "shell.h"

static char	*save_oldpwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	//env_free(tmp);
	return (0);
}

static void	save_pwd(char *save_np)
{
	size_t	size;

	size = 1024;
	save_np = malloc(size);
	if (!save_np)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	//エラー処理追記
	getcwd(save_np, size);
	free(save_np);
	return ;
}

static void	save_env(t_env *env, char *save_p, char *save_np)
{
	char	**new_p;
	char	**new_op;

	new_p = (char **)malloc(sizeof(char *) * 2);
	new_op = (char **)malloc(sizeof(char *) * 2);
	new_p[0] = ft_strjoin("PWD=", save_np);
	new_op[0] = ft_strjoin("OLDPWD=", save_p);
	new_p[1] = NULL;
	new_op[1] = NULL;
	ft_export(new_p, env);
	ft_export(new_op, env);
	free(new_p);
	free(new_p[0]);
	free(new_op);
	free(new_op[0]);
	return ;
}

int	ft_cd(char *path, t_env *env)
{
	char	*save_p;
	char	*save_op;
	char	*save_np;

	save_p = NULL;
	save_np = NULL;
	save_pwd(save_p);
	save_op = save_oldpwd(env);
	if (ft_strcmp(path, "-") == 0)
	{
		if (chdir(save_op) < 0)
			return (ft_errno(errno));
	}
	//エラー処理& FREEの仕方を後で入れる
	else
	{
		if (chdir(path) < 0)
			return (ft_errno(errno));
	}
	save_pwd(save_np);
	save_env(env, save_p, save_np);
	free(save_op);
	free(save_p);
	free(save_np);
	return (0);
}
