/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:18:55 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/18 18:21:56 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	*init_color(int r, int g, int b)
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

int		rgb_to_int(t_color *color)
{
	char	binary[25];
	char	*num;

	if (color->r < 0 || color->r > 255 || color->g < 0
		|| color->g > 255 || color->b < 0 || color->b > 255)
		return (-1);
	binary[0] = '\0';
	ft_strcat(binary, create_binary(color->r));
	ft_strcat(binary, create_binary(color->g));
	ft_strcat(binary, create_binary(color->b));
	num = ft_convert_base(binary, "01", "0123456789");
	return (ft_atoi(num));
}

int		check_color_range(t_color *color, int n)
{
	if (color->r < 0 || color->r > 255 ||
		color->g < 0 || color->g > 255 ||
		color->b < 0 || color->b > 255)
	{
		ft_printf("Error\nLine %d. ", n);
		ft_printf("Each color value should be between 0 and 255\n");
		return (-1);
	}
	return (0);
}

void	add_ambient_light(t_scene *scene, t_intersec *intersec)
{
	t_color	*shape;
	t_color	*pixel;
	t_color	*ambient;
	int		r;
	int		g;
	int		b;

	ambient = scene->ambient->color;
	r = ambient->r * scene->ambient->ratio;
	g = ambient->g * scene->ambient->ratio;
	b = ambient->b * scene->ambient->ratio;
	if (scene->ambient && scene->ambient->color->r != -1)
	{
		shape = intersec->shape->color;
		pixel = intersec->color;
		if (ambient->r == 255 && ambient->g == 255 && ambient->b == 255)
		{
			pixel->r = (shape->r > r) ? r : shape->r;
			pixel->g = (shape->g > g) ? g : shape->g;
			pixel->b = (shape->b > b) ? b : shape->b;
		}
		else
		{
			pixel->r = r + shape->r;
			pixel->g = g + shape->g;
			pixel->b = b + shape->b;
		}
	}
}
