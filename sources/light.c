/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:18 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/21 17:30:41 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*init_light_null(void)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = (t_vector *)malloc(sizeof(t_vector));
	light->color = (t_color *)malloc(sizeof(t_color));
	light->brightness = 0;
	return (light);
}

void	cap_light(t_color *color)
{
	int		max;
	float	d;

	max = (color->r > color->g) ? color->r : color->g;
	max = (max > color->b) ? max : color->b;
	if (max > 255)
	{
		d = (float)max / 255.0;
		color->r = (float)color->r / d;
		color->g = (float)color->g / d;
		color->b = (float)color->b / d;
	}
}

void	check_all_lights(t_scene *scene, t_intersec *intersec)
{
	t_list		*lst_cpy;
	t_light		*light;
	t_vector	*light_dir;
	t_vector	*point;
	t_intersec	*light_ray;
	float		light_ratio;
	float		distance;

	lst_cpy = scene->lights;
	while (lst_cpy)
	{
		light = (t_light *)lst_cpy->content;
		point = get_point(intersec->ray->origin, intersec->ray->direction, intersec->t);
		light_dir = vector_diff(light->origin, point);
		distance = length(light_dir);
		normalize(light_dir);
		light_ray = init_intersection(init_ray(point, light_dir, RAY_MAX));
		check_all_shapes(scene->shapes, light_ray);
		if (!intersected(light_ray) || (intersected(light_ray) && (light_ray->t > distance || light_ray->t < RAY_MIN)))
		{
			if (intersec->shape->id == TRIANGLE || intersec->shape->id == CYLINDER)
				light_ratio = dot_product(light_dir, intersec->normal);
			else
				light_ratio = fabs(dot_product(light_dir, intersec->normal));
			add_light_to_pixel(intersec, light, light_ratio);
		}
		lst_cpy = lst_cpy->next;
	}
	//cap_light(intersec->color);
}
/*
t_color	*color_average(t_color *c1, t_color *c2, float ratio)
{
	int		r;
	int		g;
	int		b;
	int		max;
	float	d;

	r = c1->r + c2->r * ratio;
	g = c1->g + c2->g * ratio;
	b = c1->b + c2->b * ratio;

	max = (r > g) ? r : g;
	max = (max > b) ? max : b;
	if (max > 255)
	{
		d = (float)max / 255.0;
		r = (float)r / d;
		g = (float)g / d;
		b = (float)b / d;
	}
	return (init_color(r, g, b));
}
*/
void	add_light_to_pixel(t_intersec *intersec, t_light *light, float ratio)
{
	t_color	*shape;
	t_color	color;

	shape = intersec->shape->color;
	if (!intersec->color || ratio < 0)
		return ;
	color = color_add(*intersec->color, color_multiply(color_mix_light(*shape, color_multiply(*light->color, light->brightness)), ratio));
	intersec->color->r = color.r;
	intersec->color->g = color.g;
	intersec->color->b = color.b;
}
/*
void	add_light_to_pixel(t_intersec *intersec, t_light *light, float ratio)
{
	t_color	*shape;
	t_color	*pixel;
	t_color	*mix;

	shape = intersec->shape->color;
	pixel = intersec->color;
	if (!pixel || ratio < 0)
		return ;
	// additionner les 2 couleurs avec moyenne
	mix = color_average(shape, light->color, light->brightness);
	if (light->color->r == 255 && light->color->g == 255 && light->color->b == 255)
	{
		pixel->r += shape->r * ratio * light->brightness;
		pixel->g += shape->g * ratio * light->brightness;
		pixel->b += shape->b * ratio * light->brightness;
	}
	else
	{
		pixel->r += mix->r * ratio;
		pixel->g += mix->g * ratio;
		pixel->b += mix->b * ratio;
	}
}
*/