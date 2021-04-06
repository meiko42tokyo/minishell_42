#include <stdlib.h>//pid_t chile_pd??
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

	parsed = strtok(input, separator);//きっとsprit代替可能
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
	pid_t child_pid;//書き換える
	int stat_loc;

	while (1) {
		input = readline("unixsh> ");//とりあえず文字列で保存
		command = get_input(input);//いったんそっとしておく。
		
		if (strcmp(command[0], "cd") == 0) {
			if (cd(command[1]) < 0) {
				perror(command[1]);
			}
		}
		child_pid = fork();//子プロセスがエラーおきたときに親が止まっちゃいけないからforkを作る
		if (child_pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0) {//子がいない、つまり子/子がいる、つまり親
			if (execvp(command[0], command) < 0)//こまんどを読んでくれている本体
			{
				perror(command[0]);
				exit(1);
			}
			
			printf("no message if execvp success");
		} else {
			waitpid(child_pid, &stat_loc, WUNTRACED);//親プロセスに返す：親は子をもつ
		}
		free(input);
		free(command);
	}
	return (0);

}
