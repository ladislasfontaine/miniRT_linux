#include "minirt.h"

char	*create_binary(int n)
{
	char	*temp;
	char	*byte;
	int		i;

	i = 0;
	if (!(byte = (char *)malloc(sizeof(char) * 9)))
		return (NULL);
	byte[0] = '\0';
	temp = ft_convert_base(ft_itoa(n), "0123456789", "01");
	while (ft_strlen(temp) + i < 8)
	{
		ft_strcat(byte, "0");
		i++;
	}
	ft_strcat(byte, temp);
	free(temp);
	return (byte);
}

int		rgb_to_int(int r, int g, int b)
{
	char	binary[25];
	char	*num;

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	binary[0] = '\0';
	ft_strcat(binary, create_binary(r));
	ft_strcat(binary, create_binary(g));
	ft_strcat(binary, create_binary(b));
	num = ft_convert_base(binary, "01", "0123456789");
	return (ft_atoi(num));
}
