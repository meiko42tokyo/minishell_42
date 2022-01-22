/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:34:30 by ykarasaw          #+#    #+#             */
/*   Updated: 2022/01/22 23:38:54 by sakasekaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;

	dstlen = ft_strlen(dst);
	if (dstlen >= dstsize)
		return (dstsize + ft_strlen(src));
	else
	{
		i = 0;
		while (dstlen + i < (dstsize - 1) && src[i])
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		dst[dstlen + i] = '\0';
		return (dstlen + ft_strlen(src));
	}
}
