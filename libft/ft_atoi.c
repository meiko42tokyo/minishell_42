/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykarasaw <ykarasaw@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 23:46:57 by ykarasaw          #+#    #+#             */
/*   Updated: 2020/12/26 15:51:19 by ykarasaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_spaces(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||\
				str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
			i++;
		else
			break ;
	}
	return (i);
}

int			ft_will_overflow(unsigned long n, int next_digit)
{
	if (n > (INT_MAX) / 10)
		return (1);
	if (n == (INT_MAX / 10) && next_digit > (INT_MAX % 10))
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	unsigned long	ret;
	int				i;
	int				sign;

	ret = 0;
	i = 0;
	sign = 1;
	i = check_spaces(str, i);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		if (ft_will_overflow(ret, str[i] - '0'))
			return (sign == 1 ? INT_MAX : INT_MIN);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * sign);
}
