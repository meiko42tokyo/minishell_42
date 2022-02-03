#include "shell.h"

int	ispipe(t_cmd *c)
{
	if (c->op == OP_PIPE)
		return (1);
	return (0);
}

char	**make_split_path(char **environ)
{
	char		**split_path;
	char		*tmp;
	int			i;

	split_path = NULL;
	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH", 4))
		{
			tmp = ft_strdup(environ[i] + 5);
			split_path = ft_split(tmp, ':');
			i = 0;
			free(tmp);
			break ;
		}
		i++;
	}
	return (split_path);
}

char	*make_path(char *input, char **split_path, int i)
{
	char	*tmp;
	char	*path;
	int		t;

	tmp = ft_strjoin(split_path[i], "/");
	t = ft_strncmp(input, split_path[i], ft_strlen(split_path[i]));
	free(split_path[i]);
	if (t != 0)
		path = ft_strjoin(tmp, input);
	else
		path = input;
	free(tmp);
	return (path);
}

int	do_execve(char *input, char **argv)
{
	extern char	**environ;
	char		**split_path;
	char		*path;
	int			i;
	int			re;

	split_path = make_split_path(environ);
	i = 0;
	while (split_path[i])
	{
		path = make_path(input, split_path, i++);
		if (include_redir(argv))
			argv = ft_redirect(argv, NULL, NULL);
		re = execve(path, argv, environ);
		if (!re)
		{
			free(path);
			return (0);
		}
		free(path);
	}
	free(split_path);
	return (re);
}
