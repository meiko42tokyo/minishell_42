/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 18:00:35 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/07/19 20:57:08 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	strlen1;
	size_t	strlen2;

	strlen1 = ft_strlen(s1);
	strlen2 = ft_strlen(s2);
	ret = (char*)malloc(sizeof(char) * (strlen1 + strlen2 + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s1, strlen1 + 1);
	ft_strlcat(ret, s2, strlen1 + strlen2 + 1);
	return (ret);
}
