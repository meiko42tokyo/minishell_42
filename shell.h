// Temporary aim at checking structure and use tmpShell.c

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

typedef struct	s_cmd
{
	struct s_cmd	*next;
	char		*content;
	int		pid;
	int		op;
}		t_cmd;

t_cmd	*ft_cmdnew(char *content, int op);
void	ft_cmdadd_back(t_cmd **head, t_cmd *new);
