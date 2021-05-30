#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	size_t			len;
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;

	i = 0;
	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	if (ft_strlen(s1) > ft_strlen(s2))
		len = ft_strlen(s1);
	else
		len = ft_strlen(s2);
	while (1)
	{
		if ((casted_s1[i] - casted_s2[i]) != 0)
			return (casted_s1[i] - casted_s2[i]);
		i++;
		if ((!(casted_s1[i]) && !(casted_s2[i])) || i == len)
			break ;
	}
	return (0);
}
