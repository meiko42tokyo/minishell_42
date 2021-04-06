/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:02:09 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/07/19 18:17:16 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *s;

	s = (unsigned char *)src;
	while (n--)
	{
		*(unsigned char *)dst++ = *(unsigned char *)s;
		if (*s++ == (unsigned char)c)
			return (dst);
	}
	return (NULL);
}
