#include "shell.h"
#include "libft/libft.h"

int	exec_buildin(char **command, t_env *env)
{
	//strncmpにしなくていいかあとで確認
	//ft_strcmp->ft_ft_strcmp
	if (ft_strcmp(command[0], "cd") == 0)
		return (ft_cd(command[1], env));
	else if (ft_strcmp(command[0], "echo") == 0)
		return (ft_echo(command));
	else if (ft_strcmp(command[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(command[0], "export") == 0)
		return (ft_export(&command[1], env));
	else if (ft_strcmp(command[0], "unset") == 0)
		return (ft_unset(command, env));
	else if (ft_strcmp(command[0], "env") == 0)
		return  (ft_env(env));
	else if (ft_strcmp(command[0], "exit") == 0)
		return (ft_exit(command));
	return (1);
}

int	is_buildin(char **command)
{
	if (!command || !command[0])
		return (0);
	//どれかに引っかかる場合は１を返す
	else if (ft_strcmp(command[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(command[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(command[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(command[0], "export") == 0)
		return (1);
	else if (ft_strcmp(command[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(command[0], "env") == 0)
		return (1);
	else if (ft_strcmp(command[0], "exit") == 0)
		return (1);
	return (0);
	
}
