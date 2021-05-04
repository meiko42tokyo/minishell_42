/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 23:25:55 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/07/18 23:31:53 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getchar_fd(int fd)
{
	static char	buf[1024];
	static char	*bufp;
	static int	i;

	bufp = buf;
	i = 0;
	if (i == 0)
	{
		i = read(fd, buf, 1);
		bufp = buf;
	}
	if (--i >= 0)
	{
		return (*bufp++);
	}
	return (-1);
}
