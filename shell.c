#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"
#include <errno.h>
//No.定義：https://nxmnpg.lemoda.net/ja/2/errno
//errno：https://linuxjm.osdn.jp/html/LDP_man-pages/man3/errno.3.html

int	cd(char *path) {
	return chdir(path);
}

char **get_input(char *input) {
	char **command = malloc(8 * sizeof(char *));
	if (command == NULL)
	{
		ft_putstr_fd("malloc fail", 2);
		ft_putstr_fd("\n", 2);
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
		errno = 0;
		if (strcmp(command[0], "cd") == 0) {
			if (cd(command[1]) < 0) {
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
			}
			continue ;
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			//エラーの書き方最後にチェック
			ft_putstr_fd("fork error", 2);
			ft_putstr_fd("\n", 2);
		}
		if (child_pid == 0) {
			errno = 0;
			//execve:https://linuxjm.osdn.jp/html/LDP_man-pages/man2/execve.2.html?
			execve(path, command, envp);
			if (errno){
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd("\n", 2);
				exit(errno);
			}
			printf("no message if execvp success");
		} else {
			//エラー処理ここにも多分必要
			waitpid(child_pid, &stat_loc, WUNTRACED);
		}
		free(input);
		free(command);
	}
	return (0);

}
