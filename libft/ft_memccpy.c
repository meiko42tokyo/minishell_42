/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:02:09 by ykarasaw          #+#    #+#             */
/*   Updated: 2022/01/22 23:42:25 by sakasekaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s;

	s = (unsigned char *)src;
	while (n--)
	{
		*(unsigned char *)dst++ = *(unsigned char *)s;
		if (*s++ == (unsigned char)c)
			return (dst);
	}
	return (NULL);
}
