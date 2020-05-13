/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:22:17 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/13 19:04:42 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// faire des tests avec différents coordonnés
int		triangle_intersection(t_intersec *intersec, t_shape *tri)
{
	t_vector	*a;
	t_vector	*b;
	t_vector	*normal;
	float d;
	float t;
	t_vector	*e0;
	t_vector	*e1;
	t_vector	*e2;
	t_vector	*c0;
	t_vector	*c1;
	t_vector	*c2;
	t_vector	*point;

	a = vector_diff(tri->p2, tri->p1);
	b = vector_diff(tri->p3, tri->p1);
	normal = cross_product(a, b);
	normalize(normal);

	d = dot_product(normal, tri->p1);
	t = - (dot_product(normal, intersec->ray->origin) + d) / dot_product(normal, intersec->ray->direction);

	if (dot_product(normal, intersec->ray->direction) == 0.0)
		return (0);
	point = point_on_ray(*intersec->ray, t);
	e0 = vector_diff(tri->p2, tri->p1);
	e1 = vector_diff(tri->p3, tri->p2);
	e2 = vector_diff(tri->p1, tri->p3);
	c0 = vector_diff(point, tri->p1);
	c1 = vector_diff(point, tri->p2);
	c2 = vector_diff(point, tri->p3);
	if (t <= RAY_MIN || t >= intersec->t)
		return (0);
	if (dot_product(normal, cross_product(e0, c0)) > 0 &&
		dot_product(normal, cross_product(e1, c1)) > 0 &&
		dot_product(normal, cross_product(e2, c2)) > 0)
	{
		intersec->t = t;
		intersec->shape = tri;
		intersec->normal = normal;
	}
	return (0);
}