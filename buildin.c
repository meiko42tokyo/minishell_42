#include "shell.h"
#include "libft/libft.h"

int	is_buildin(char **command)
{
	//どれかに引っかかる場合は１を返す
	//strncmpにしなくていいかあとで確認
	if (strcmp(command[0], "cd") == 0)
		return (ft_cd(command[1]));
	//else if (strcmp(command[0], "echo") == 0)
	//	return (ft_echo(command[1]));
	else if (strcmp(command[0], "pwd") == 0)
		return (ft_pwd());
	//else if (strcmp(command[0], "export") == 0)
	//	return (ft_export(command[1]));
	//else if (strcmp(command[0], "unset") == 0)
	//	return (ft_unset(command[1]));
	//else if (strcmp(command[0], "env") == 0)
	//	return (ft_env(command[1]));
	//else if (strcmp(command[0], "exit") == 0)
	//	return (ft_exit(command[1]));
	return (1);
}
