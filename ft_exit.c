#include "shell.h"

static int	check_spaces(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
				str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
			i++;
		else
			break ;
	}
	return (i);
}

int	ft_will_overflow_ex(unsigned long n, int next_digit)
{
	if (n > (LONG_MAX) / 10)
		return (1);
	if (n == (LONG_MAX / 10) && next_digit > (LONG_MAX % 10))
		return (1);
	return (0);
}

static void	exit_error(const char *str, int num)
{
	ft_putstr_fd("exit\n", 1);
	if (str)
	{
		ft_putstr_fd("exit\nbash: exit :", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
	}
	exit (num);
}

static ssize_t	ft_exit_atoi(const char *str, ssize_t ret)
{
	int		i;
	int		sign;

	ret = 0;
	i = 0;
	sign = 1;
	i = check_spaces(str, i);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit_error(str, 255);
		if (ft_will_overflow_ex(ret, str[i] - '0'))
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		ret = ret * 10 + str[i++] - '0';
	}
	return (ret * sign);
}

int	ft_exit(char **command)
{
	ssize_t	num;

	reset_termcap();
	num = 0;
	if (command[1] == NULL)
		exit_error(NULL, 0);
	num = ft_exit_atoi(command[1], num);
	if (num == -1 && ft_strcmp(command[1], "-1") != 0)
		exit_error(command[1], 255);
	if (command[1] != NULL && command[2])
		return (ft_error_str("too many argment"));
	if (num < 0)
	{
		num = num * (-1);
		if (num > 255)
			num %= 256;
		exit_error(NULL, 256 - num);
	}
	else
	{
		if (num > 255)
			num %= 256;
		exit_error(NULL, num);
	}
	return (0);
}
