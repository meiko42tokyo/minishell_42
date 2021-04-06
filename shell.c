#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/libft.h"

int	cd(char *path) {
	return chdir(path);//OK
	//相対パスは今後対応
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

int	main()
{
	char **command;
	char *input;
	pid_t child_pid;
	int stat_loc;

	//if (argc != 1)
	//エラー処理
	while (1)
	{
		ft_putstr_fd("unixsh> ", 0);
		//エラー処理追記必要あり
		get_next_line(0, &input);
		//input = readline("unixsh> ");//NG:printfで>を出力して、あとはgetnextlineの標準入力バージョンで文字列を出力
		command = get_input(input);//いったんそっとしておくけど二次元配列に格納
		
		if (strcmp(command[0], "cd") == 0)
		{
			if (cd(command[1]) < 0)
			{
				perror(command[1]);//NG:strerrorかerroroに変える：最後に処理で良い
			}
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0)
		{//folkに成功した場合
			if (execvp(command[0], command) < 0)//NG:コマンド読んでくれる関数execveは使える
			{
				perror(command[0]);//NG
				exit(1);
			}
			printf("no message if execvp success");
		}
		else 
		{
			//while (!WIFEXITED(stat_loc) && !WIFSIGNALED(stat_loc))
			waitpid(child_pid, &stat_loc, WUNTRACED);
			//OK:子プロセスが終わるまで親プロセスを停止
			//https://www.delftstack.com/ja/howto/c/waitpid-in-c/
			//man_waitpid:https://linuxjm.osdn.jp/html/LDP_man-pages/man2/wait.2.html
			//WUNTRACED:終了だけでなく、他に停止した子プロセスについて報告。
			//errnoここで使うかも
			//https://www.ibm.com/docs/ja/zos/2.3.0?topic=functions-waitpid-wait-specific-child-process-end
		}
		free(input);
		free(command);
	}
	return (0);
}
