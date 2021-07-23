#include "shell.h"

int	is_in_quoto(int state)
{
	if (state == SINGLE_Q || state == DOUBLE_Q)
		return (1);
	else
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
