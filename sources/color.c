#include "minirt.h"

t_color		*init_color(int r, int g, int b)
{
	t_color	*color;

	color = (t_color *)malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

static char	*create_binary(int n)
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

int		rgb_to_int(t_color *color)//int r, int g, int b)
{
	char	binary[25];
	char	*num;

	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
		return (-1);
	binary[0] = '\0';
	ft_strcat(binary, create_binary(color->r));
	ft_strcat(binary, create_binary(color->g));
	ft_strcat(binary, create_binary(color->b));
	num = ft_convert_base(binary, "01", "0123456789");
	return (ft_atoi(num));
}

int		check_color_range(t_color *color)
{
	if (color->r < 0 || color->r >255 ||
		color->g < 0 || color->g >255 ||
		color->b < 0 || color->b >255)
	{
		ft_putstr("Error\nEach color value should be between 0 and 255\n");
		return (-1);
	}
	return (0);
}
