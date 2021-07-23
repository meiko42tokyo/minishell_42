#include "shell.h"

int	heredoc_exist(char *input)
{
	int	state;

	state = NOT_Q;
	while (*input != '\0')
	{
		if (*input == '\"' || *input == '\'')
			manage_state(&state, *input);
		input++;
	}
	return (0);
}

void	heredoc(char *input)
{
	printf("heredoc:%s\n", input);
}
