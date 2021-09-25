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

	identifier = NULL;
	// expand quoto
	//if (*id == '\"' || *input == '\'')
		// skip and add null	
	free (id);
	return (identifier);
}

char	*get_identifier(char *input)
{
	int	len;
	char	*id;
	int 	state;
	char	*save;

	state = NOT_Q;
	input += 2;
	while (ft_isspace(*input))
		input++;
	len = ft_strlen(input);
	if (ft_strchr(input, ' '))
		len = ft_strchr(input, ' ') - input;
	id = ft_strndup(input, len);
	save = id;
	while(id != '\0')
	{
		printf("id:%s\n", id);
		if (*id == '\"' || *id == '\'')
			br(&state, &id);
		else
		{
			if (*id == '\0')
				break;
			id++;
		}
	}
	return (save);
}

int	heredoc(char *input)
{
	char	*identifier;

	identifier = get_identifier(input);
	// store input while line != identifier
	// connect saved str to standard input
	// remove << and aaa from argv
	printf("ientifier:%s\n", identifier);
	return (0);
}
