/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:41 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 15:53:48 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		sphere_intersection(t_intersec *intersec, t_shape *sphere)
{
	float		discriminant;
	int			inside;
	t_ray		*local_ray;
	t_vector	v;

	local_ray = init_ray(malloc_vector(vector_diff(*intersec->ray->origin,
		*sphere->center)), intersec->ray->direction, intersec->ray->max_t);
	if (!local_ray)
		return (0);
	v.x = length_square(*local_ray->direction);
	v.y = 2 * dot_product(*local_ray->direction, *local_ray->origin);
	v.z = length_square(*local_ray->origin) - square(sphere->diameter / 2.0);
	free(local_ray->origin);
	free(local_ray);
	discriminant = square(v.y) - (4 * v.x * v.z);
	if (discriminant < 0.0f)
		return (0);
	inside = sphere_points(intersec, v.x, v.y, discriminant);
	if (inside > 0)
	{
		intersec->shape = sphere;
		sphere_normal_vector(intersec, inside);
		return (1);
	}
	return (0);
}

int		sphere_points(t_intersec *intersec, float a, float b, float d)
{
	float	t1;
	float	t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if (t1 > RAY_MIN && t1 < intersec->t)
	{
		intersec->t = t1;
		return (1);
	}
	else if (t2 > RAY_MIN && t2 < intersec->t)
	{
		intersec->t = t2;
		return (2);
	}
	else
		return (0);
}

int		sphere_normal_vector(t_intersec *intersec, int inside)
{
	t_vector	point;

	point = get_point(*intersec->ray->origin
			, *intersec->ray->direction, intersec->t);
	if (inside == 2)
		copy_vector(intersec->normal, vector_mul(
			vector_diff(point, *intersec->shape->center), -1));
	else
		copy_vector(intersec->normal, vector_diff(point,
			*intersec->shape->center));
	normalize(intersec->normal);
	return (0);
}
