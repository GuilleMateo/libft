#include "libft.h"
int		ft_atoi(const char *str)
{
	int			i;
	int			sgn;
	long long	res;

	i = 0;
	sgn = 1;
	res = 0;
	while (str[i] == ' ' || ((9 <= str[i]) && (str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sgn = -1;
		i++;
	}
	while (str[i] && ('0' <= str[i]) && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sgn * res);
}
