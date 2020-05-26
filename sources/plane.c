/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:06 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 10:23:30 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	init_plane(t_vector position, t_vector normal)
{
	t_plane	pl;

	pl.position = position;
	pl.normal = normal;
	return (pl);
}

int		plane_intersection(t_intersec *intersec, t_shape *plane)
{
	float d_dot_n;
	float t;

	d_dot_n = dot_product(*intersec->ray->direction, *plane->normal);
	if (d_dot_n == 0.0f)
		return (0);
	t = dot_product(vector_diff(*plane->position, *intersec->ray->origin)
		, *plane->normal) / d_dot_n;
	if (t <= RAY_MIN || t >= intersec->t)
		return (0);
	intersec->t = t;
	intersec->shape = plane;
	if (get_angle(intersec->ray->direction, plane->normal) < 90.0)
		copy_vector(intersec->normal, vector_mul(*plane->normal, -1));
	else
		copy_vector(intersec->normal, *plane->normal);
	return (1);
}
