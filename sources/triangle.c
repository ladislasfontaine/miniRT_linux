/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 16:22:17 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/14 13:10:09 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		triangle_intersection(t_intersec *intersec, t_shape *tri)
{
	t_vector	*v0v1;
	t_vector	*v0v2;
	t_vector	*pvec;
	t_vector	*tvec;
	t_vector	*normal;
	float		det;
	float		invdet;
	float		u;
	float		v;
	float		t;

	v0v1 = vector_diff(tri->p2, tri->p1);
	v0v2 = vector_diff(tri->p3, tri->p1);
	normal = cross_product(v0v1, v0v2);
	pvec = cross_product(intersec->ray->direction, v0v2);
	det = dot_product(v0v1, pvec);

	if ((det > -RAY_MIN && det < RAY_MIN) || fabs(det) < RAY_MIN)
		return (0);
	invdet = 1 / det;
	tvec = vector_diff(intersec->ray->origin, tri->p1);
	u = dot_product(tvec, pvec) * invdet;
	if (u < 0 || u > 1)
		return (0);
	v = dot_product(intersec->ray->direction, cross_product(tvec, v0v1)) * invdet;
	if (v < 0 || u + v > 1)
		return (0);
	t = dot_product(v0v2, cross_product(tvec, v0v1)) * invdet;
	intersec->t = t;
	intersec->shape = tri;
	if (get_angle(intersec->ray->direction, normal) < 90.0)
		intersec->normal = init_vector(-(normal->x), -(normal->y), -(normal->z));
	else
		intersec->normal = normal;
	return (0);
}