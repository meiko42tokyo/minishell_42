#include "shell.h"

//ファイル名修正はやるかあとで確認

static int	redirect(int fd, int stdfd, int *in_out)
{
	if (fd == -1)
	{
	//エラー処理
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
	//0666はあとで
	if (ft_strcmp(command[0], ">") == 0)
		fd = redirect(open(command[1], O_WRONLY | O_CREAT | O_TRUNC, 0666), 1, out);
	else if (ft_strcmp(command[0], ">>") == 0)
		fd = redirect(open(command[1], O_WRONLY | O_CREAT | O_APPEND, 0666), 1, out);
	else if (ft_strcmp(command[0], "<") == 0)
		fd = redirect(open(command[1], O_RDONLY), 0, in);
	if (fd == -1)
		return (NULL);
	free(command[0]);
	command[0] = NULL;
	free(command[1]);
	command[1] = NULL;
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
	if (ft_strcmp(command, ">") == 0 || ft_strcmp(command, ">>") == 0\
			|| ft_strcmp(command, "<") == 0)
		return (1);
	return (0);
}

char	**ft_redirect(char **command, int *in, int *out)
{
	int	i;
	int	j;
	//char	**n_command;

	if (!command)
		return (NULL);
	i = 0;
	while(command[i])
		i++;
	//if (!(n_command = ft_calloc(i + 1, sizeof(char *))))
	//	return (NULL);
	i = 0;
	j = 0;
	while (command[i])
	{
		if(!is_redir(command[i]))
			i++;
			//		n_command[j++] = command[i++];
		else
		{
			if (!(redirect_free(command + i, in, out)))
				return (return_free(command));
			i += 2;
		}
	}
	//free(command);
	return (command);
}
