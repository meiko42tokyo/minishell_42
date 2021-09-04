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

char	*get_identifier(char *input)
{
	int	len;

	input += 2;
	while (ft_isspace(*input))
		input++;
	len = ft_strlen(input);
	if (ft_strchr(input, ' '))
		len = ft_strchr(input, ' ') - input;
	return (ft_strndup(input, len));
}

int	heredoc(char *input)
{
	// get identifier
	// expand identifier
	char	*identifier;

	identifier = get_identifier(input);
	// store input while line != identifier
	// connect saved str to standard input
	// remove << and aaa from argv
	printf("heredoc:%s\n", input);
	return (0);
}
