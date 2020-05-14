/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 13:10:33 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/14 18:53:33 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			cylinder_intersection(t_intersec *intersec, t_shape *cy)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		t;
	float		y;
	float		dist;
	t_vector	*p0;

	p0 = vector_diff(intersec->ray->origin, cy->center);
	a = square(intersec->ray->direction->x) + square(intersec->ray->direction->z);
	b = intersec->ray->direction->x * p0->x + intersec->ray->direction->z * p0->z;
	c = square(p0->x) + square(p0->z) - square(cy->diameter / 2);
	delta = square(b) - a * c;

	if (delta < RAY_MIN)
		return (0);
	t = (-b - sqrtf(delta)) / a;
	if (t <= RAY_MIN || t >= intersec->t)
		return (0);
	y = p0->y + t * intersec->ray->direction->y;
	if (y > cy->height + RAY_MIN || y < -RAY_MIN)
	{
		// checker intersection avec les bases
		if (intersect_base(intersec, cy, &(t_vector){cy->center->x, (cy->center->y + cy->height), cy->center->z}, &dist))
		{
			intersec->shape = cy;
			intersec->t = dist;
			intersec->normal = cylinder_normal(cy, get_point(intersec->ray->origin, intersec->ray->direction, t));
		}
		if (intersect_base(intersec, cy, cy->center, &dist) && dist > RAY_MIN && intersec->t >= dist)
		{
			intersec->shape = cy;
			intersec->t = dist;
			intersec->normal = cylinder_normal(cy, get_point(intersec->ray->origin, intersec->ray->direction, t));
		}
		return (0);
	}
	intersec->shape = cy;
	intersec->t = t;
	intersec->normal = cylinder_normal(cy, get_point(intersec->ray->origin, intersec->ray->direction, t));

	return (0);
}

int			intersect_base(t_intersec *intersec, t_shape *cy, t_vector *c, float *dist)
{
	t_vector	*normal;
	t_vector	*p0;
	t_vector	*p;
	float		A;
	float		B;
	float		C;
	float		D;

	normal = cylinder_normal(cy, c);
	p0 = vector_diff(intersec->ray->origin, cy->center);
	A = normal->x;
	B = normal->y;
	C = normal->z;
	D = - (A * (c->x - cy->center->x) + B * (c->y - cy->center->y) + C * (c->z - cy->center->z));
	if (A * intersec->ray->direction->x + B * intersec->ray->direction->y + C * intersec->ray->direction->z)
		return (0);
	*dist = - (A * p0->x + B * p0->y + C * p0->z + D) / (A * intersec->ray->direction->x + B * intersec->ray->direction->y + C * intersec->ray->direction->z);
	if (*dist < RAY_MIN)
		return (0);
	p = vector_add(p0, vector_mul(intersec->ray->direction, *dist));
	if (square(p->x) + square(p->z) - square(cy->diameter / 2.0) > RAY_MIN)
		return (0);
	return (1);
}

t_vector	*cylinder_normal(t_shape *cy, t_vector *p)
{
	t_vector	*c0;
	t_vector	*n;
	float		radius;

	radius = cy->diameter / 2.0;
	if (p->x < (cy->center->x + radius) && p->x < (cy->center->x - radius) &&
		p->z < (cy->center->z + radius) && p->z < (cy->center->z - radius))
	{
		return (init_vector(0, 1, 0));
	}
	c0 = init_vector(cy->center->x, p->y, cy->center->z);
	n = vector_diff(p, c0);
	normalize(n);
	free(c0);
	return (n);
}
