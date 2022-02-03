#include "shell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**copy_argvs(char *argv[], char **old_argv, size_t len, int token)
{
	char	**new_argv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_argv = (char **)malloc(sizeof (char *) \
			* (len + is_redirect(token) + 1));
	if (new_argv == NULL)
		return (NULL);
	while (old_argv[i])
	{
		new_argv[i] = ft_strdup(old_argv[i]);
		i++;
	}
	if (is_redirect(token))
		new_argv[i++] = ft_strdup(put_token(token));
	while (argv[j])
		new_argv[i++] = argv[j++];
	new_argv[i] = NULL;
	free_argv(old_argv);
	free(argv);
	return (new_argv);
}

int	append_arg(char *argv[], t_cmd **head)
{
	t_cmd	*node;
	size_t	old_len;
	size_t	new_len;
	char	**old_argv;

	node = *head;
	while (node)
	{
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	old_argv = node->argv;
	old_len = ft_strplen(node->argv);
	new_len = ft_strplen(argv);
	node->argv = copy_argvs(argv, old_argv, old_len + new_len, node->op);
	if (node->argv == NULL)
		return (1);
	return (0);
}	

char	**get_latestargv(t_cmd **head)
{
	int		index;
	t_cmd	*node;

	index = 0;
	node = *head;
	while (node)
	{
		if (node->next == NULL)
		{
			while (node->argv[index])
			{
				index++;
			}
			break ;
		}
		node = node->next;
	}
	return (&node->argv[index - 1]);
}

int	is_allspace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isspace(s[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
