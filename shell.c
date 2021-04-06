#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

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

int	main() {
	char **command;
	char *input;
	pid_t child_pid;
	int stat_loc;

	while (1) {
		input = readline("unixsh> ");
		command = get_input(input);
		
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
			if (execvp(command[0], command) < 0)
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
