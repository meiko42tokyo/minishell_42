#include "shell.h"
#include "libft/libft.h"

int	is_buildin(char **command)
{
	//どれかに引っかかる場合は１を返す
	if (strcmp(command[0], "cd") == 0)
		return (ft_cd(command[1]));
	//elseif ();
	//elseif ();
	return (1);
}
