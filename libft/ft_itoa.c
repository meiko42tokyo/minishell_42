/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 04:16:47 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/07/19 18:09:02 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*reverse_str(char *str)
{
	char	tmp;
	size_t	strlen;
	size_t	i;

	i = 0;
	strlen = ft_strlen(str);
	while (i < strlen / 2)
	{
		tmp = str[i];
		str[i] = str[strlen - i - 1];
		str[strlen - i - 1] = tmp;
		i++;
	}
	return (str);
}

static int	count_digit(int n, int isnegative)
{
	int	count;

	count = isnegative;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	add_num_to_str(int n, char *str)
{
	int	num;
	int	i;

	i = 0;
	while (n != 0)
	{
		num = n % 10;
		str[i] = num + '0';
		n /= 10;
		i++;
	}
	return (i);
}

static char	*make_str(int n, int isnegative, int i)
{
	char *str;

	str = (char*)malloc(sizeof(char) * (count_digit(n, isnegative) + 1));
	if (str == NULL)
		return (NULL);
	i = add_num_to_str(n, str);
	if (isnegative)
		str[i++] = '-';
	str[i] = '\0';
	return (reverse_str(str));
}

char		*ft_itoa(int n)
{
	int		isnegative;
	int		i;

	isnegative = 0;
	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		isnegative = 1;
		n = -n;
	}
	return (make_str(n, isnegative, i));
}
