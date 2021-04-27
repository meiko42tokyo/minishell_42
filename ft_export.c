#include "shell.h"

int	ft_export(char **command, char **environ)
{
	char		*name;
	int			sp;//sp is "="
	int			i;

	sp = ft_strchr(command[0], '=') - command[0];//=までの文字の長さをくっつける
	printf("%d\n", sp);
	name = ft_strndup(command[0], sp);
	printf("%s\n", name);
	i = 0;
	while (environ[i]) 
	{
		if (ft_strncmp(name, environ[i], sp) == 0)//文字列がenvironのどれかと一致した場合
		{
//			environ[i] = (char*)malloc(sizeof(char) * (ft_strlen(command[0]) + 1));//あとでエラー処理
			environ[i] = ft_memmove(environ[i], command[0], ft_strlen(command[0]));//引数が複数のときは要検証
			environ[i][ft_strlen(command[0])] = '\0';
			printf("insert:environ[%d] = %s\n", i, environ[i]);
			return (0);
		}
		i++;
	}
	environ = (char **)malloc(sizeof(char *) * (i + 1));
	environ[i] = (char*)malloc(sizeof(char) * (ft_strlen(command[0]) + 1));//あとでエラー処理
	environ[i] = ft_memmove(environ[i], command[0], ft_strlen(command[0]));//引数が複数のときは要検証
	//environ[i] = command[0];
	printf("add:environ[%d] = %s\n", i, environ[i]);
	return (0);
}
