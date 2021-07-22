#include "shell.h"

int	print_error(char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (0);
}

void	manage_state(int *state, char c)
{
	if (c == '\'')
	{
		if (*state == NOT_Q)
			*state = SINGLE_Q;
		else if (*state == SINGLE_Q)
			*state = NOT_Q;
	}
	else if (c == '\"')
	{
		if (*state == NOT_Q)
			*state = DOUBLE_Q;
		else if (*state == DOUBLE_Q)
			*state = NOT_Q;
	}
}


int	valid_semicolon(char *input)
{
	int	state;

	state = NOT_Q;
	while (*input != '\0')
	{
		if (*input == '\"' || *input == '\'')
			manage_state(&state, *input);
		else if (state == NOT_Q && *input == ';' && input[1] == ';')
			return (print_error(";;"));
		printf("input:%c\n", *input);
		input++;
	}
	return (1);
}

int	valid_syntax(char *input)
{
	printf("ft_strlen(input):%zu\n", ft_strlen(input));
	if (!valid_semicolon(input))
		return (0);
	return (1);
}
