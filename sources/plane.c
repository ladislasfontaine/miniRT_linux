/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:06 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 15:38:39 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*init_plane(t_shape *plane, t_vector *position, t_vector *normal)
{
	plane->position = position;
	plane->normal = normal;
	return (plane);
}

int		plane_intersection(t_intersec *intersec, t_shape *plane)
{
	float d_dot_n;
	float t;

	d_dot_n = dot_product(intersec->ray->direction, plane->normal);
	if (d_dot_n == 0.0f)
		return (0);
	t = dot_product(vector_diff(plane->position, intersec->ray->origin)
		, plane->normal) / d_dot_n;
	if (t <= RAY_MIN || t >= intersec->t)
		return (0);
	intersec->t = t;
	intersec->shape = plane;
	intersec->normal = plane->normal;
	return (1);
}
