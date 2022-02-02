#include "shell.h"

int	print_error(char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (1);
}

int	check_pipe_syntax(char *input)
{
	if (*input == '|')
	{
		while (ft_isspace(input[1]))
			input++;
		if (input[1] == '|')
			return (1);
	}
	return (0);
}

int	check_redirect_syntax(char *input)
{
	if (is_redirect(get_op(input)))
	{
		while (ft_isspace(input[1]))
			input++;
		if (input[1] == '\0')
			return (1);
	}
	return (0);
}

int	check_syntax(char *input, int *heredoc)
{
	int	i;

	i = ft_strcmp(input, "<<");
	if (i != 0 && (*heredoc = 1))
		return (1);
	else if (check_pipe_syntax(input))
		return (print_error("|"));
	else if (!ft_strncmp(input, ";;", 2))
		return (print_error(";;"));
	else if (!ft_strncmp(input, ";", 1))
		return (print_error(";"));
	else if (check_redirect_syntax(input))
		return (print_error("new_line"));
	return (0);
}

int	syntax_error(char **input)
{
	int		state;
	int		heredocs;
	char	*save;

	state = NOT_Q;
	save = *input;
	while (**input != '\0')
	{
		heredocs = 0;
		if (**input == '\"' || **input == '\'')
			manage_state(&state, **input);
		if (state == NOT_Q && check_syntax(*input, &heredocs))
		{
			if (heredocs)
				return (heredoc(input));
			return (1);
		}
		(*input)++;
	}
	*input = save;
	return (0);
}
