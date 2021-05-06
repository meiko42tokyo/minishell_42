#include "shell.h"

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

static int			ft_exit_atoi(const char *str)
{
	size_t	ret;
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
			return (-1);
		if (ft_will_overflow(ret, str[i] - '0'))
			return (sign == 1 ? INT_MAX : INT_MIN);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	return (ret * sign);
}

//負の数＝エラー
//引数２つ＝？？
//intmaxより上＝エラー
//256以上＝255とで割った数のあまり
int	ft_exit(char **command)
{
	size_t	num;

	if (command[2])//なぜかexitでここはいる
		return (ft_error_str("too many argment"));
	if (command[1] == NULL)
		exit (0);
	num = ft_exit_atoi(command[1]);
	if (num < 0)
		return (ft_error_str("invalid argment"));
	else
	{
		if (num > 255)
			num %= 256;
		ft_putstr_fd("exit\n", 2);
		exit (num);
	}
	return (0);
}
