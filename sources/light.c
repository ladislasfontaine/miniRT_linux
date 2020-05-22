/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:18 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 16:16:33 by lafontai         ###   ########.fr       */
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

void	check_all_lights(t_scene *scene, t_intersec *intersec)
{
	t_lights	l;

	l.lst_cpy = scene->lights;
	while (l.lst_cpy)
	{
		l.light = (t_light *)l.lst_cpy->content;
		l.point = get_point(intersec->ray->origin, intersec->ray->direction,
							intersec->t);
		l.light_dir = vector_diff(l.light->origin, l.point);
		l.distance = length(l.light_dir);
		normalize(l.light_dir);
		l.light_ray = init_intersection(
						init_ray(l.point, l.light_dir, RAY_MAX));
		check_all_shapes(scene->shapes, l.light_ray);
		if (!intersected(l.light_ray) || (intersected(l.light_ray) &&
		(l.light_ray->t > l.distance - RAY_MIN || l.light_ray->t < RAY_MIN)))
		{
			l.light_ratio = dot_product(l.light_dir, intersec->normal);
			add_light_to_pixel(intersec, l.light, l.light_ratio);
		}
		l.lst_cpy = l.lst_cpy->next;
	}
}

void	add_light_to_pixel(t_intersec *intersec, t_light *light, float ratio)
{
	t_color	*shape;
	t_color	color;

	shape = intersec->shape->color;
	if (!intersec->color || ratio < 0)
		return ;
	color = color_add(*intersec->color, color_multiply(color_mix_light(*shape,
			color_multiply(*light->color, light->brightness)), ratio));
	intersec->color->r = color.r;
	intersec->color->g = color.g;
	intersec->color->b = color.b;
}
