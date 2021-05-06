#include "shell.h"
#include "libft/libft.h"

int	exec_buildin(char **command, t_env *env)
{
	//strncmpにしなくていいかあとで確認
	//ft_strncmp->ft_ft_strncmp
	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
		return (ft_cd(command[1]));
	else if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (ft_echo(command));
	else if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		return (ft_pwd());
	else if (ft_strncmp(command[0], "export", ft_strlen(command[0])) == 0)
		return (ft_export(&command[1], env));
	//else if (ft_strncmp(command[0], "unset", ft_strlen(command[0])) == 0)
	//	return (ft_unset(command[1]));
	else if (ft_strncmp(command[0], "env", ft_strlen(command[0])) == 0)
		return  (ft_env(env));
	else if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (ft_exit(command));
	return (1);
}

int	is_buildin(char **command)
{
	//どれかに引っかかる場合は１を返す
	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
		return (1);
	else if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (1);
	else if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		return (1);
	else if (ft_strncmp(command[0], "export", ft_strlen(command[0])) == 0)
		return (1);
	else if (ft_strncmp(command[0], "unset", ft_strlen(command[0])) == 0)
		return (1);
	else if (ft_strncmp(command[0], "env", ft_strlen(command[0])) == 0)
		return (1);
	else if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (1);
	return (0);
	
}
