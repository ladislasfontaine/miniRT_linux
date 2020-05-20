/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:22:17 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 16:14:08 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	triangle_calculations(t_intersec *intersec, t_shape *tri, t_triangle *t)
{
	t->v0v1 = vector_diff(tri->p2, tri->p1);
	t->v0v2 = vector_diff(tri->p3, tri->p1);
	t->normal = cross_product(t->v0v1, t->v0v2);
	t->pvec = cross_product(intersec->ray->direction, t->v0v2);
	t->det = dot_product(t->v0v1, t->pvec);
}

int		triangle_intersection(t_intersec *intersec, t_shape *tri)
{
	t_triangle	t;

	triangle_calculations(intersec, tri, &t);
	if ((t.det > -RAY_MIN && t.det < RAY_MIN) || fabs(t.det) < RAY_MIN)
		return (0);
	t.invdet = 1 / t.det;
	t.tvec = vector_diff(intersec->ray->origin, tri->p1);
	t.u = dot_product(t.tvec, t.pvec) * t.invdet;
	if (t.u < 0 || t.u > 1)
		return (0);
	t.v = dot_product(intersec->ray->direction,
			cross_product(t.tvec, t.v0v1)) * t.invdet;
	if (t.v < 0 || t.u + t.v > 1)
		return (0);
	t.t = dot_product(t.v0v2, cross_product(t.tvec, t.v0v1)) * t.invdet;
	intersec->t = t.t;
	intersec->shape = tri;
	if (get_angle(intersec->ray->direction, t.normal) < 90.0)
		intersec->normal = init_vector(-(t.normal->x), -(t.normal->y)
										, -(t.normal->z));
	else
		intersec->normal = t.normal;
	return (0);
}
