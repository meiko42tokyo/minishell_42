#include "shell.h"

static char	*save_oldpwd(t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while(tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->name) == 0)
		{
			ft_putstr_fd(tmp->value, 2);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (NULL);
}

static char	*save_pwd()
{
	size_t size;
	char *buf;

	size = 1024;
	buf = malloc(size);
	if (!buf)
	{
		ft_putstr_fd("malloc failure\n", 2);
		return (NULL);
	}
	getcwd(buf, size);
	return (buf);
}

int	ft_cd(char *path, t_env *env)
{
	char	*save_p;
	char	*save_op;
	char	*save_np;
	char	*new_p;
	char	*new_op;

	save_p = save_pwd(); 
	save_op = save_oldpwd(env); 
	if (!env || !path)
		return (1);
	if (ft_strcmp(path, "-") == 0)
	{
		if (!save_op)
		{
			//save_opが最初からセットされている問題解決の必要あり
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		if (chdir(save_op) < 0)
			return (ft_errno(errno));
	}
	else
	{
		if (chdir(path) < 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	save_np = save_pwd(); 
	new_p = ft_strjoin("PWD=", save_np);
	new_op = ft_strjoin("OLDPWD=", save_p);
	ft_export(&new_op, env);
	ft_export(&new_p, env);
	free(save_np);
	free(save_p);
	free(save_op);
	free(new_op);
	free(new_p);
	return (0);
}
