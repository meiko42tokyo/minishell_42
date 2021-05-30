#include "shell.h"

t_cmd	*ft_cmdnew(char *argv[], int op)
{
	t_cmd	*node;

	node = (t_cmd*)malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	node->argv = argv;
	node->pid = -1;
	node->op = op;
	return (node);
}

void	ft_cmdadd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*node;

	if (*head == NULL)
	{
		*head = new;
		return;
	}
	node = *head;
	while (node)
	{
		if (node->next == NULL)
		{
			node->next = new;
			break;
		}
		node = node->next;
	}
	node->next = NULL; 
	return ;
}

void	ft_print_cmdlist(t_cmd **head)
{
	t_cmd	*node;
	int	index;
	int	arg_order;
	char	op;

	index = 0;
	if (*head == NULL)
	{
		printf("cmd head null\n");
		return ;
	}
	node = *head;
	while (node)
	{
		printf("cmd[%d]:\n", index++);
		arg_order = 0;
		while (node->argv[arg_order])
		{
			printf("  argv[%d]:%s\n", arg_order, node->argv[arg_order]);	
			arg_order++;
		}
		if (node->op == OP_SEP)
			op = ';';
		if (node->op == OP_PIPE)
			op = '|';
		if (node->op == OTHER)
			op = 'O';
		printf("  op:%c\n", op);
		if (node->next == NULL)
		{
			break ;
		}
		node = node->next;
	}
}	
