/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 22:07:05 by ykarasaw          #+#    #+#             */
/*   Updated: 2022/01/22 23:46:47 by sakasekaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)hs);
	i = 0;
	while (hs[i])
	{
		j = 0;
		while (hs[i + j] == needle[j] && hs[i + j] != '\0' && i + j < len)
		{
			if (needle[j + 1] == '\0')
			{
				return ((char *)hs + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
