#include "shell.h"

int	main() {
	// test data
	char *content = "ls -l";
	t_cmd *head;	
	t_cmd *new;
	head = ft_cmdnew(content, 124);
	new = ft_cmdnew(content, 124);
	ft_cmdadd_back(&head, new);
	
	// debug
	while (head)
	{
		printf("head:%s, %c\n", head->content, head->op); 
		if (head->next == NULL)
			break;
		head=head->next;
	}
}
