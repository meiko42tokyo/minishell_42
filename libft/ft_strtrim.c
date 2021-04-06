/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 18:29:15 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/07/19 20:48:40 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	if (set == NULL || !*set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i])
	{
		ptr = ft_strchr(set, s1[i]);
		if (ptr == NULL)
			break ;
		i++;
	}
	j = ft_strlen(s1);
	while (j > i)
	{
		ptr = ft_strchr(set, s1[j]);
		if (ptr == NULL)
			break ;
		j--;
	}
	return (ft_substr(&s1[i], 0, j - i + 1));
}
