/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 13:10:33 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/21 15:43:38 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		find_cylinder_base(t_intersec *inter, t_shape *cy, t_shape *plane)
{
	float d_dot_n;
	float t;

	d_dot_n = dot_product(inter->ray->direction, plane->normal);
	if (d_dot_n == 0.0)
		t = -1;
	else
		t = dot_product(vector_diff(plane->position, inter->ray->origin),
			plane->normal) / d_dot_n;
	if (t > RAY_MIN && t < inter->t &&
		length(vector_diff(plane->position, get_point(inter->ray->origin,
		inter->ray->direction, t))) <= (cy->diameter / 2))
	{
		inter->shape = cy;
		inter->t = t;
		inter->normal = plane->normal;
	}
}

float		check_cylinder_base(t_shape *plane, t_vector *inter, t_vector *n)
{
	float d_dot_n;
	float t;

	d_dot_n = dot_product(n, n);
	if (d_dot_n == 0.0f)
		return (-1);
	t = dot_product(vector_diff(plane->position, inter), n) / d_dot_n;
	if (t < 0 || t >= RAY_MAX)
		return (-1);
	return (t);
}

t_vector	*cylinder_normal(t_vector *inter, t_shape *cy, float t3)
{
	return (vector_diff(inter, get_point(cy->center, cy->normal,
			(cy->height - t3 - cy->height / 2.0))));
}

int			cylinder_calculations(t_intersec *intersec, t_shape *cy, t_cyl *c)
{
	c->cross = cross_product(intersec->ray->direction, cy->normal);
	c->p0 = vector_diff(intersec->ray->origin, cy->center);
	c->cross2 = cross_product(c->p0, cy->normal);
	c->a = dot_product(c->cross, c->cross);
	c->b = 2 * dot_product(c->cross, c->cross2);
	c->c = dot_product(c->cross2, c->cross2) - (pow(cy->diameter / 2, 2)
			* dot_product(cy->normal, cy->normal));
	c->det = pow(c->b, 2) - 4 * c->a * c->c;
	if (c->det < RAY_MIN)
		return (0);
	c->t1 = (-c->b - sqrtf(c->det)) / (2 * c->a);
	c->t2 = (-c->b + sqrtf(c->det)) / (2 * c->a);
	return (1);
}

int			cylinder_intersection(t_intersec *intersec, t_shape *cy)
{
	t_cyl	c;

	if (!cylinder_calculations(intersec, cy, &c))
		return (0);
	c.t = (c.t1 > RAY_MIN && c.t1 < intersec->t) ? c.t1 : -1;
	if (c.t2 > RAY_MIN && c.t2 < intersec->t && c.t == -1)
		c.t = c.t2;
	if (c.t == -1)
		return (0);
	c.inter = get_point(intersec->ray->origin, intersec->ray->direction, c.t);
	c.plane1 = init_plane(get_point(cy->center, cy->normal, cy->height / 2),
				cy->normal);
	c.plane2 = init_plane(get_point(cy->center, vector_mul(cy->normal, -1),
				cy->height / 2), vector_mul(cy->normal, -1));
	c.t3 = check_cylinder_base(c.plane1, c.inter, cy->normal);
	c.t4 = check_cylinder_base(c.plane2, c.inter, vector_mul(cy->normal, -1));
	if (c.t3 >= 0 && c.t3 <= cy->height && c.t4 >= 0 && c.t4 <= cy->height)
	{
		intersec->shape = cy;
		intersec->t = c.t;
		intersec->normal = cylinder_normal(c.inter, cy, c.t3);
	}
	find_cylinder_base(intersec, cy, c.plane1);
	find_cylinder_base(intersec, cy, c.plane2);
	return (0);
}
