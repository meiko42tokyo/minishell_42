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
	node->next->next = NULL; 
	return ;
}

int	ft_argv_len(t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->argv[len])
	{
		len++;
	}
	return (len);
}

int	ft_print_cmdsize(t_cmd **head)
{
	t_cmd	*node;
	int	index;

	node = *head;
	index = 0;
	while (node)
	{
		index++;
		if (node->next == NULL)
		{
			break;
		}
		node = node->next;
	}
	return (index);
}

int	check_argvsize(t_cmd *node)
{
	int	size;

	size = 0;
	while (node->argv[size])
		size++;
	return (size);
}

void	free_cmdlist(t_cmd **cmd)
{
	t_cmd	*next_node;
	int	arg_order;

	if (!cmd)
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

void	ft_print_cmdlist(t_cmd **head)
{
	t_cmd	*node;
	int	index;
	int	arg_order;
	char	*op;

	index = 0;
	if (*head == NULL)
	{
		//printf("cmd head null\n");
		return ;
	}
	node = *head;
	while (node)
	{
		arg_order = 0;
		while (node->argv[arg_order])
		{
			arg_order++;
		}
		if (node->op == OP_SEP)
			op = ";";
		if (node->op == OP_PIPE)
			op = "|";
		if (node->op == RD_LESSER)
			op = "<";
		if (node->op == RD_GREATER)
			op = ">";
		if (node->op == RD_EXTRACT)
			op = ">>";
		if (node->op == OTHER)
			op = "O";
		if (node->op == BR_DOUBLE)
			op = "\"";
		if (node->op == BR_SINGLE)
			op = "\'";
		if (node->next == NULL)
		{
			break ;
		}
		node = node->next;
	}
}	
