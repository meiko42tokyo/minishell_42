/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:51:00 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/11/26 15:01:40 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_strs(char const *s, char c)
{
	size_t	count;
	size_t	index;

	count = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] != c && s[index + 1] == c)
			count++;
		if (s[index] != c && s[index + 1] == '\0')
			count++;
		index++;
	}
	return (count);
}

void	make_str(char **head, char *ptr, char c, size_t len)
{
	char	*next_del;
	size_t	i;

	i = 0;
	while (len)
	{
		next_del = ft_strchr(ptr, c);
		if (next_del == NULL)
			head[i] = ft_substr(ptr, 0, ft_strlen(ptr));
		if ((next_del - ptr) < 1)
			ptr++;
		else
		{
			head[i] = ft_substr(ptr, 0, next_del - ptr);
			while (*next_del == c && *next_del)
			{
				next_del++;
			}
			ptr = next_del;
			i++;
		}
		len--;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**head;
	char	*ptr;
	char	*tmp;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = count_strs(s, c);
	head = (char**)ft_calloc(len + 1, sizeof(char*));
	if (head == NULL)
		return (NULL);
	ptr = ft_strtrim((char *)s, " ");
	tmp = ptr;
	make_str(head, ptr, c, len);
	free(tmp);
	return (head);
}
