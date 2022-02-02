#include "shell.h"

int	heredoc_exist(char *input, int *times)
{
	int	state;

	state = NOT_Q;
	while (*input != '\0')
	{
		if (*input == '\"' || *input == '\'')
			manage_state(&state, *input);
		if (!ft_strncmp(input, "<<", 2))
			(*times)++;
		input++;
	}
	return (*times);
}

char	*expand_identifier(char *id)
{
	char	*identifier;
	int	state;

	state = NOT_Q;
	identifier = id;
	while (id)
	{
		if (*id == '\"' || *id == '\'')
			br(&state, &id);
		else
		{
			if (*id == '\0')
				break ;
			id++;
		}
	}
	return (identifier);
}

char	*get_identifier(char *input)
{
	int	len;
	char	*id;

	input += 2;
	while (ft_isspace(*input))
		input++;
	len = ft_strlen(input);
	if (ft_strchr(input, ' '))
		len = ft_strchr(input, ' ') - input;
	id = ft_strndup(input, len);
	return (expand_identifier(id));
}

void	free_set(char **line, char *src)
{
	free(*line);
	*line = src;
}

void	store_line(char *identifier)
{
	char	*line;
	char	*save;

	line = ft_strjoin("", NULL);
	save = ft_strjoin("", NULL);
	write(1, "> ", 2);
	while (get_next_line(STDIN_FILENO, &line))
	{
		if (ft_strncmp(line, identifier, ft_strlen(line)) == 0)
			break ;
		else
			write(1, "> ", 2);
		free_set(&line, ft_strjoin(line, "\n"));
		free_set(&save, ft_strjoin(save, line));
	}
}

void	skip_heredoc(t_cmd **head)
{
	t_cmd	*cmd;
	int	arg_i;

	cmd = *head;
	while (cmd)
	{
		arg_i = 0;
		while (cmd->argv[arg_i])
		{
			if (!ft_strncmp(cmd->argv[arg_i], "<<", 2))
			{
				strpshift(cmd->argv, arg_i);
				strpshift(cmd->argv, arg_i);
			}
			arg_i++;
		}
		if (cmd->next == NULL)
			break ;
		cmd = cmd->next;
	}
}

int	heredoc(char **input)
{
	char	*identifier;
	
	reset_termcap();
	identifier = get_identifier(*input);
	store_line(identifier);
	//ret = remove_heredoc(*input);
	//if (ft_strchr(*input, ' '))
	//{
	//	len = ft_strchr(*input, ' ') - *input;
	//}
	// count number of identifier?
		// num until <<
		// num until ' '
		// num until all
	// remove << and aaa from argv
	set_termcap();
	return (0);
}
