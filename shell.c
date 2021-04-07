#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

int	cd(char *path) {
	return chdir(path);
}

char **get_input(char *input) {
	char **command = malloc(8 * sizeof(char *));
	if (command == NULL)
	{
		perror("malloc failed");
		exit(1);
	}
	char *separator = " ";
	char *parsed;
	int index = 0;

	parsed = strtok(input, separator);
	while (parsed != NULL) {
		command[index] = parsed;
		index++;
		
		parsed = strtok(NULL, separator);
	}
	command[index] = NULL;
	return command;
}

int	main(int argc, char **argv, char **envp) {
	char **command;
	char *input;
	char *path;
	pid_t child_pid;
	int stat_loc;

	//あとでなんとかする
	argc = 1;
	argv = NULL;
	while (1) {
		ft_putstr_fd("> ", 0);
		get_next_line(0, &input);
		command = get_input(input);
		path = ft_strjoin("/bin/", input);
		
		if (strcmp(command[0], "cd") == 0) {
			if (cd(command[1]) < 0) {
				perror(command[1]);
			}
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0) {
			if (execve(path, command, envp) < 0)
			{
				perror(command[0]);
				exit(1);
			}
			printf("no message if execvp success");
		} else {
			waitpid(child_pid, &stat_loc, WUNTRACED);
		}
		free(input);
		free(command);
	}
	return (0);

}
