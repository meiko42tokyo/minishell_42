#include "shell.h"


int	shell_error()
{
	write(2, "minishell: syntax error", 23);
	write(2, "\n", 1);
	return (1);
}

int	avoid_segfault(char *input)
{
	if (*input == '|')
	{
		while (ft_isspace(input[1]))
			input++;
		if (input[1] == '\0')
			return (1);
	}
	return (0);	
}
