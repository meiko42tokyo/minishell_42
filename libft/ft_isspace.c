int	ft_isspace(int c)
{	
	if (c == ' ' || c == '\t' || c == '\n' ||\
			c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);

}

