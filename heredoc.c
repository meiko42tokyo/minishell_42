#include "shell.h"

int	heredoc_exist(char *input, int *times)
{
	int	state;

	state = NOT_Q;
	while (*input != '\0')
	{
		if (*input == '\"' || *input == '\'')
			manage_state(&state, *input);
		if (!ft_strncmp(input, "<<", 2))
			(*times)++;
		input++;
	}
	return (*times);
}

char	*expand_identifier(char *id)
{
	char	*identifier;
	int 	state;

	state = NOT_Q;
	identifier = id;
	while (id != '\0')
	{
		if (*id == '\"' || *id == '\'')
			br(&state, &id);
		else
		{
			if (*id == '\0')
				break;
			id++;
		}
	}
	return (identifier);
}

char	*get_identifier(char *input)
{
	int	len;
	char	*id;

	input += 2;
	while (ft_isspace(*input))
		input++;
	len = ft_strlen(input);
	if (ft_strchr(input, ' '))
		len = ft_strchr(input, ' ') - input;
	id = ft_strndup(input, len);
	return (expand_identifier(id));
}

void	store_line(char *identifier)
{
	char	*line;
	char	*save;
	char	*tmp;

	line = NULL;
	save = ft_strjoin("", NULL);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (ft_strncmp(line, identifier, ft_strlen(line)) == 0)
		{
			break;
		}
		tmp = ft_strjoin(save, line);
		printf("in while, tmp :%s\n", tmp);
		free(save);
		save = tmp;
	}
	printf("save: %s\n", save);
	//store_as_stdin(save);
}

int	heredoc(char *input)
{
	char	*identifier;

	identifier = get_identifier(input);
	store_line(identifier);
	// remove << and aaa from argv
	printf("ientifier:%s\n", identifier);
	return (0);
}
