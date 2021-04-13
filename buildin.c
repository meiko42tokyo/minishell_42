#include "shell.h"

int	isbuildin(command)
{
	//どれかに引っかかる場合は１を返す
	if (strcmp(command[0], "cd") == 0)
		return (is_cd(command));
	elseif ();
	elseif ();

	return (0);
}
