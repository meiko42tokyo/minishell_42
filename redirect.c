#include "shell.h"
#include "libft/libft.h"

int	redirect(int fd, int stdfd, int *in_out)
{
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (fd);
	}
	if (in_out && *in_out == -1)
		*in_out = dup(stdfd);
	dup2(fd, stdfd);
	close(fd);
	return (fd);
}

static char	**redirect_free(char **command, int *in, int *out)
{
	int	fd;

	fd = 0;
	if (ft_strcmp(command[0], ">") == 0)
		fd = redirect(open(command[1], O_WRONLY \
			| O_CREAT | O_TRUNC, 0666), 1, out);
	else if (ft_strcmp(command[0], ">>") == 0)
		fd = redirect(open(command[1], O_WRONLY \
				| O_CREAT | O_APPEND, 0666), 1, out);
	else if (ft_strcmp(command[0], "<<") == 0)
	{
		fd = redirect(g_shell->heredoc_fd[0], 0, in);
		close(g_shell->heredoc_fd[1]);
	}
	else if (ft_strcmp(command[0], "<") == 0)
		fd = redirect(open(command[1], O_RDONLY), 0, in);
	free(command[0]);
	command[0] = NULL;
	free(command[1]);
	command[1] = NULL;
	if (fd == -1)
		return (NULL);
	return (command + 2);
}

char	**return_free(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		free(command[i++]);
	free(command);
	return (NULL);
}

int	is_redir(char *command)
{
	if (ft_strcmp(command, ">") == 0 || ft_strcmp(command, ">>") \
		   	 == 0 || ft_strcmp(command, "<") == 0 \
			|| ft_strcmp(command, "<<") == 0)
		return (1);
	return (0);
}

char	**ft_redirect(char **command, int *in, int *out)
{
	int	i;

	if (!command)
		return (NULL);
	i = 0;
	while (command[i])
	{
		if (!is_redir(command[i]))
			i++;
		else
		{
			if (!(redirect_free((command + i), in, out)))
				return (NULL);
			i += 2;
		}
	}
	return (command);
}
