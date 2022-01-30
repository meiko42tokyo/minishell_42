/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 03:35:34 by ykarasaw          #+#    #+#             */
/*   Updated: 2022/01/30 10:45:43 by sakasekaw        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	slen;
	char	*ret;

	slen = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * slen + 1);
	if (ret == NULL)
		return (NULL);
	ret = (char *)ft_memcpy(ret, s1, slen);
	ret[slen] = '\0';
	return (ret);
}
