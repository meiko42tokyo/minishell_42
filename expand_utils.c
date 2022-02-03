#include "shell.h"

void	strshift(char *word)
{
	size_t	len;

	len = ft_strlen(word);
	ft_memmove(word, word + 1, len - 1);
	word[len - 1] = '\0';
}

void	ft_mempshift(char **dst, char **src, size_t len)
{
	while (len--)
		*dst++ = *src++;
}

void	strpshift(char **argv, int arg_i)
{
	size_t	len;
	char	*cur_arg;
	int		cur_i;

	len = 0;
	cur_arg = argv[arg_i];
	cur_i = arg_i;
	while (argv[arg_i++])
		len++;
	free(cur_arg);
	cur_arg = NULL;
	ft_mempshift(argv + cur_i, argv + cur_i + 1, len - 1);
	argv[cur_i + len - 1] = NULL;
}

int	strnshift(char *word, int dis, char *head)
{
	size_t	len;

	len = ft_strlen(word + 1);
	ft_memmove(word, word + dis + 1, len - dis);
	word[len - dis] = '\0';
	if (*head == '\0')
		return (1);
	return (0);
}

int	is_escape(char c)
{
	if (c == '\"' || c == '\"' || c == '`' || c == '$')
		return (1);
	else
		return (0);
}
