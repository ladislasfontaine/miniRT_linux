#include "libft.h"

int		ft_numlen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len += 1;
	}
	while (n > 9)
	{
		n = n / 10;
		len += 1;
	}
	return (len);
}