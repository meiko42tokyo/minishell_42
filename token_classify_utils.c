#include "shell.h"

int	is_op(int *token)
{
	if (*token == OP_PIPE || *token == OP_SEP)
		return (1);
	else
		return (0);
}

int	is_redirect(int token)
{
	if (token == RD_LESSER || token == RD_GREATER \
			|| token == RD_EXTRACT || token == RD_INSERT)
		return (1);
	else
		return (0);
}

int	is_two_char(int *token)
{
	if (*token == RD_EXTRACT || *token == RD_INSERT)
		return (1);
	else
		return (0);
}

int	is_token_br(int token)
{
	if (token == BR_DOUBLE || token == BR_SINGLE)
		return (1);
	else
		return (0);
}
