#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft/libft.h"

int main() {

	pid_t child_pid;
	printf("start of minishell.\n");
	char *s;
	int i;
	child_pid = fork();
	while(child_pid != 0) {

		while (get_next_line(0, &s) > 0) {
			// parse for user input
			if (!ft_strncmp(s, "echo ", 5))
			{
				i = 0;
				while (i < 5)
				{
					s++;
					i++;
				}
				printf("%s\n", s);
			}
		}
	}
	return (0);
}
