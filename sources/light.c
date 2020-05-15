/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:18 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/15 11:48:46 by lafontai         ###   ########.fr       */
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
			add_light_to_pixel(intersec, light_ratio);
		}
		lst_cpy = lst_cpy->next;
	}
}

void	add_light_to_pixel(t_intersec *intersec, float ratio)
{
	t_color	*shape;
	t_color	*pixel;

	shape = intersec->shape->color;
	pixel = intersec->color;
	if (!pixel || ratio < 0)
		return ;
	pixel->r += shape->r * ratio;
	pixel->g += shape->g * ratio;
	pixel->b += shape->b * ratio;
	if (pixel->r > shape->r)
		pixel->r = shape->r;
	if (pixel->g > shape->g)
		pixel->g = shape->g;
	if (pixel->b > shape->b)
		pixel->b = shape->b;
}
