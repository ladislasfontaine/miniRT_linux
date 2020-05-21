/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:18:55 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/21 17:10:14 by lafontai         ###   ########.fr       */
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

t_color	color_mul(t_color *c, float f)
{
	return ((t_color){(float)c->r * f, (float)c->g * f, (float)c->b * f});
}

void	check_color_range(t_scene *scene, t_color *color)
{
	if (color->r < 0 || color->r > 255 ||
		color->g < 0 || color->g > 255 ||
		color->b < 0 || color->b > 255)
		error_and_quit(scene, "Each color value should be between 0 and 255");
}

void	add_ambient_light(t_scene *scene, t_intersec *intersec)
{
	t_color	color;

	color = color_mix_light(*intersec->shape->color, color_multiply(*scene->ambient->color, scene->ambient->ratio));
	intersec->color->r = color.r;
	intersec->color->g = color.g;
	intersec->color->b = color.b;
}
/*
void	add_ambient_light(t_scene *scene, t_intersec *intersec)
{
	t_color	*shape;
	t_color	*pixel;
	t_color	*ambient;
	t_color	c;

	ambient = scene->ambient->color;
	c = color_mul(ambient, scene->ambient->ratio);
	if (scene->ambient && scene->ambient->color->r != -1)
	{
		shape = intersec->shape->color;
		pixel = intersec->color;
		if (ambient->r == 255 && ambient->g == 255 && ambient->b == 255)
		{
			pixel->r = (shape->r > c.r) ? c.r : shape->r;
			pixel->g = (shape->g > c.g) ? c.g : shape->g;
			pixel->b = (shape->b > c.b) ? c.b : shape->b;
		}
		else
		{
			pixel->r = c.r + shape->r;
			pixel->g = c.g + shape->g;
			pixel->b = c.b + shape->b;
		}
	}
}
*/