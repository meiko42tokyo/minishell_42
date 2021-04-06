#include <stdlib.h>//pid_t chile_pd??
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

int	cd(char *path) {
	return chdir(path);//OK
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

int	main(int argc, char **argv)
{
	char **command;
	char *input;
	pid_t child_pid;//これ何か調べる
	int stat_loc;

	//if (argc != 1)
	//エラー処理
	while (1) {
		printf("unixsh> ");
		//エラー処理追記必要あり
		get_next_line(0, &input);
		//input = readline("unixsh> ");//NG:printfで>を出力して、あとはgetnextlineの標準入力バージョンで文字列を出力
		command = get_input(input);//いったんそっとしておくけど二次元配列に格納
		
		if (strcmp(command[0], "cd") == 0) {
			if (cd(command[1]) < 0) {
				perror(command[1]);//NG:strerrorかerroroに変える：最後に処理で良い
			}
		}
		child_pid = fork();//子プロセスがエラーおきたときに親が止まっちゃいけないからforkを作る
		if (child_pid < 0)
		{
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0) {//folkに成功した場合
			if (execvp(command[0], command) < 0)//NG:コマンド読んでくれる関数execveは使える
			{
				perror(command[0]);//NG
				exit(1);
			}
			printf("no message if execvp success");
		} else {
			waitpid(child_pid, &stat_loc, WUNTRACED);
			//OK:子プロセスが終わるまで親プロセスを停止
			//https://www.delftstack.com/ja/howto/c/waitpid-in-c/
			//man_waitpid:https://linuxjm.osdn.jp/html/LDP_man-pages/man2/wait.2.html
			//WUNTRACED:終了だけでなく、他に停止した子プロセスについて報告。
			//errnoここで使うかも
			//https://www.ibm.com/docs/ja/zos/2.3.0?topic=functions-waitpid-wait-specific-child-process-end
		}
		free(input);
		free(command);//多分、二次元配列分フリー必要？？
	}
	return (0);

}
