/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 23:13:44 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/11/26 16:14:16 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	gnl_strlen(char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strndup(char *s, size_t len)
{
	char	*ret;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (tmp == NULL)
		return (NULL);
	ret = tmp;
	while (len--)
		*tmp++ = *s++;
	*tmp = '\0';
	return (ret);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ret;
	char	*tmp;
	size_t	strlen1;
	size_t	strlen2;

	strlen1 = gnl_strlen(s1);
	strlen2 = gnl_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (strlen1 + strlen2 + 1));
	if (ret == NULL)
		return (NULL);
	tmp = ret;
	while (strlen1--)
		*ret++ = *s1++;
	while (strlen2--)
		*ret++ = *s2++;
	*ret = '\0';
	return (tmp);
}

char	*gnl_strchr(char *s, char c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}
