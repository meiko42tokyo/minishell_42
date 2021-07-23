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

int	valid_pipe(char *input)
{
	int	state;

	state = NOT_Q;
	while (*input != '\0')
	{
		if (*input == '\"' || *input == '\'')
			manage_state(&state, *input);
		else if (state == NOT_Q && *input == '|')
		{
			while (ft_isspace(input[1]))
				input++;
			if (input[1] == '|')
				return print_error("|");
		}
		input++;
	}
	return (1);
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
		input++;
	}
	return (1);
}

int	valid_syntax(char *input)
{
	
	if (!valid_semicolon(input) || !valid_pipe(input))
		return (0);
	return (1);
}
