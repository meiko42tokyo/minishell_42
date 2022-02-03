/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 09:58:26 by ykarasaw          #+#    #+#             */
/*   Updated: 2022/02/02 19:41:12 by sakasekaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int set_buf_gnl(char **buf, int *n)
{
    *buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (*buf == NULL)
    {
        *n = -1;
        return (0);
    }
    return (1);
}

char    *ft_read_till_newline(char *tmp, char **memo, int fd, int *n)
{
    char        *newline;
    char        *buf;

    if (!set_buf_gnl(&buf, n))
        return (NULL);
    while (1)
    {
        newline = gnl_strchr(*memo, '\n');
        if (newline == NULL)
            *n = read(fd, buf, BUFFER_SIZE);
        if (newline != NULL || *n <= 0)
            break ;
        buf[*n] = '\0';
        if (*memo == NULL)
            *memo = ft_strndup(buf, gnl_strlen(buf));
        else
        {
            tmp = gnl_strjoin(*memo, buf);
            free(*memo);
            *memo = tmp;
        }
        newline = gnl_strchr(*memo, '\n');
    }
    free(buf);
    return (newline);
}

int	make_a_line(char **line, char **memo, char *newline, char *tmp)
{
	*line = ft_strndup(*memo, newline - *memo);
	tmp = ft_strndup(newline + 1, gnl_strlen(newline + 1));
	free(*memo);
	*memo = NULL;
	*memo = tmp;
	return (1);
}

int	make_lastline(char **line, char **memo)
{
	if (*memo == NULL)
		*line = ft_strndup("", 1);
	else
	{
		*line = *memo;
		*memo = NULL;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*memo;
	int			n;
	char		*tmp;
	char		*newline;

	n = 0;
	*line = NULL;
	tmp = NULL;
	newline = ft_read_till_newline(tmp, &memo, fd, &n);
	if (n == -1)
	{
		free(memo);
		memo = NULL;
		return (-1);
	}
	if (newline != NULL)
		return (make_a_line(line, &memo, newline, tmp));
	else
		return (make_lastline(line, &memo));
}
