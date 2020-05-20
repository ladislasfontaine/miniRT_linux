/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:12 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 16:13:22 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray		*init_ray(t_vector *u, t_vector *v, float t)
{
	t_ray	*new;

	if (!(new = (t_ray *)malloc(sizeof(t_ray))))
		return (NULL);
	new->origin = u;
	new->direction = v;
	new->max_t = t;
	return (new);
}

t_vector	*point_on_ray(t_ray ray, float t)
{
	float		x;
	float		y;
	float		z;
	t_vector	*point;

	x = ray.origin->x + ray.direction->x * t;
	y = ray.origin->y + ray.direction->y * t;
	z = ray.origin->z + ray.direction->z * t;
	point = init_vector(x, y, z);
	return (point);
}

void		check_rays(t_scene *scene, char *data, t_vector vec, t_camera *cam)
{
	t_intersec	*intersec;
	t_ray		*ray;
	int			intersect;
	float		u;
	float		v;

	u = (2.0f * vec.x) / (float)scene->res->w - 1.0f;
	v = (-2.0f * vec.y) / (float)scene->res->h + 1.0f;
	if (!(ray = make_ray(scene, cam, u, v)))
		error_and_quit(scene, "Malloc failed");
	if (!(intersec = init_intersection(ray)))
		error_and_quit(scene, "Malloc failed");
	check_all_shapes(scene->shapes, intersec);
	intersect = (intersected(intersec)) ? 1 : 0;
	if (intersect)
	{
		add_ambient_light(scene, intersec);
		check_all_lights(scene, intersec);
	}
	data[(int)vec.z] = (intersect) ? intersec->color->b : 0;
	data[(int)vec.z + 1] = (intersect) ? intersec->color->g : 0;
	data[(int)vec.z + 2] = (intersect) ? intersec->color->r : 0;
	data[(int)vec.z + 3] = 0;
	clear_intersection(intersec);
}
