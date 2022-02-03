#include "shell.h"

void	free_cmdlist(t_cmd **cmd)
{
	t_cmd	*next_node;
	int		arg_order;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		next_node = (*cmd)->next;
		arg_order = 0;
		while ((*cmd)->argv[arg_order])
		{
			free((*cmd)->argv[arg_order]);
			(*cmd)->argv[arg_order] = NULL;
			arg_order++;
		}
		free((*cmd)->argv);
		free(*cmd);
		*cmd = next_node;
	}
	*cmd = NULL;
}

static char	*check_op(t_cmd *node)
{
	if (node->op == OP_SEP)
		return (";");
	if (node->op == OP_PIPE)
		return ("|");
	if (node->op == RD_LESSER)
		return ("<");
	if (node->op == RD_GREATER)
		return (">");
	if (node->op == RD_EXTRACT)
		return (">>");
	if (node->op == OTHER)
		return ("O");
	if (node->op == BR_DOUBLE)
		return ("\"");
	if (node->op == BR_SINGLE)
		return ("\'");
	return (NULL);
}

void	ft_print_cmdlist(t_cmd **head)
{
	t_cmd	*node;
	int		index;
	int		arg_order;
	char	*op;

	index = 0;
	if (*head == NULL)
		return ;
	node = *head;
	while (node)
	{
		arg_order = 0;
		while (node->argv[arg_order])
			arg_order++;
		op = check_op(node);
		if (node->next == NULL)
			break ;
		node = node->next;
	}
}	
