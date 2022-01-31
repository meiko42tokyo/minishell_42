/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 15:50:22 by ykarasaw          #+#    #+#             */
/*   Updated: 2022/01/22 23:47:21 by sakasekaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	decide_retlen(size_t strlen, size_t len)
{
	if (strlen < len)
		return (strlen);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*str;
	size_t	strlen;
	size_t	retlen;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)&s[start];
	strlen = ft_strlen(str);
	retlen = decide_retlen(strlen, len);
	ret = (char *)malloc(sizeof(char) * retlen + 1);
	if (ret == NULL)
		return (NULL);
	ret = ft_memcpy(ret, str, retlen);
	ret[retlen] = '\0';
	return (ret);
}
