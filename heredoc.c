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

void	heredoc(char *input, int times)
{
	while (times--)
	{
		printf("heredoc:%s\n", input);
	}
}
