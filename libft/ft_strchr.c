/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 16:57:10 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/07/19 20:32:24 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	if (*ptr == (char)c)
		return (ptr);
	while (ptr[i++])
	{
		if (ptr[i] == c)
			return (ptr + i);
	}
	return (NULL);
}
