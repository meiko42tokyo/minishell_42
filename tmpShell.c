#include "shell.h"

int	main() {
	// test data
	char *content1 = "echo aaa";
	char *content2 = "sleep 10";
	char *content3 = "echo bbb";
	t_cmd *head;	
	t_cmd *new1;
	t_cmd *new2;
	head = ft_cmdnew(content1, 124);
	new1 = ft_cmdnew(content2, 124);
	new2 = ft_cmdnew(content3, 0);
	ft_cmdadd_back(&head, new1);
	ft_cmdadd_back(&head, new2);
	
	// debug
	while (head)
	{
		printf("head:%s, %c\n", head->content, head->op); 
		if (head->next == NULL)
			break;
		head=head->next;
	}
}
