#include "shell.h"

char	**set_ops(void)
{
	char	**ops;

	ops = (char **)malloc(sizeof (char *) * (OPS_SIZE + 1));
	ops[OP_SEP] = ";";
	ops[OP_PIPE] = "|";
	ops[RD_LESSER] = "<";
	ops[RD_GREATER] = ">";
	ops[RD_EXTRACT] = ">>";
	ops[RD_INSERT] = "<<";
	ops[BR_DOUBLE] = "\"";
	ops[BR_SINGLE] = "\'";
	ops[OPS_SIZE] = 0;
	return (ops);
}

int	get_op(char *op)
{
	if (ft_strncmp(op, ";", 1) == 0)
		return (OP_SEP);
	if (ft_strncmp(op, "|", 1) == 0)
		return (OP_PIPE);
	if (ft_strncmp(op, "<<", 2) == 0)
		return (RD_INSERT);
	if (ft_strncmp(op, "<", 1) == 0)
		return (RD_LESSER);
	if (ft_strncmp(op, ">>", 2) == 0)
		return (RD_EXTRACT);
	if (ft_strncmp(op, ">", 1) == 0)
		return (RD_GREATER);
	if (ft_strncmp(op, "\"", 1) == 0)
		return (BR_DOUBLE);
	if (ft_strncmp(op, "\'", 1) == 0)
		return (BR_SINGLE);
	return (OTHER);
}

char	*put_token(int token)
{
	if (token == OP_SEP)
		return (";");
	if (token == OP_PIPE)
		return ("|");
	if (token == RD_LESSER)
		return ("<");
	if (token == RD_GREATER)
		return (">");
	if (token == RD_EXTRACT)
		return (">>");
	if (token == RD_INSERT)
		return ("<<");
	if (token == BR_DOUBLE)
		return ("\"");
	if (token == BR_SINGLE)
		return ("\'");
	return (NULL);
}

