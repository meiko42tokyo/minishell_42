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
	free(tmp);
	return (0);
}

static char	*save_pwd(void)
{
	size_t	size;
	char	*buf;

	size = 1024;
	buf = malloc(size);
	if (!buf)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	//エラー処理追記
	getcwd(buf, size);
	return (buf);
}

int	ft_cd(char *path, t_env *env)
{
	char	*save_p;
	char	*save_op;
	char	*save_np;
	char	**new_p;
	char	**new_op;

	save_p = save_pwd();
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
	save_np = save_pwd();
	new_p = (char **)malloc(sizeof(char*) * 2);
	new_op = (char **)malloc(sizeof(char*) * 2);
	new_p[0] = ft_strjoin("PWD=", save_np);
	new_op[0] = ft_strjoin("OLDPWD=", save_p);
	new_p[1] = NULL;
	new_op[1] = NULL; 
	ft_export(new_p, env);
	ft_export(new_op, env);
	free(new_p);
	free(new_op);
	return (0);
}
