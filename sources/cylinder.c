/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 13:10:33 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/21 11:57:52 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		find_cylinder_base(t_intersec *intersec, t_shape *cy, t_shape *plane)
{
	float d_dot_n;
	float t;

	d_dot_n = dot_product(intersec->ray->direction, plane->normal);
	if (d_dot_n == 0.0f)
		t = -1;
	else
		t = dot_product(vector_diff(plane->position, intersec->ray->origin), plane->normal) / d_dot_n;
	if (t > RAY_MIN && t < intersec->t && length(vector_diff(plane->position, get_point(intersec->ray->origin, intersec->ray->direction, t))) <= (cy->diameter / 2))
	{
		intersec->shape = cy;
		intersec->t = t;
		intersec->normal = plane->normal;
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
	return (vector_diff(inter, get_point(cy->center, cy->normal, (t3 - cy->height / 2))));
}

int			cylinder_intersection(t_intersec *intersec, t_shape *cy)
{
	t_vector	*cross;
	t_vector	*cross2;
	t_vector	*p0;
	t_vector	*inter;
	t_shape		*plane1;
	t_shape		*plane2;
	float		a;
	float		b;
	float		c;
	float		det;
	float		t;
	float		t1;
	float		t2;
	float		t3;
	float		t4;

	cross = cross_product(intersec->ray->direction, cy->normal);
	p0 = vector_diff(intersec->ray->origin, cy->center);
	cross2 = cross_product(p0, cy->normal);
	a = dot_product(cross, cross);
	b = 2 * dot_product(cross, cross2);
	c = dot_product(cross2, cross2) - (pow(cy->diameter / 2, 2) * dot_product(cy->normal, cy->normal));
	det = pow(b, 2) - 4 * a * c;
	if (det < RAY_MIN)
		return (0);
	t1 = (-b - sqrtf(det)) / (2 * a);
	t2 = (-b + sqrtf(det)) / (2 * a);
	if (t1 > RAY_MIN && t1 < intersec->t)
		t = t1;
	else if (t2 > RAY_MIN && t2 < intersec->t)
		t = t2;
	else
		return (0);

	inter = get_point(intersec->ray->origin, intersec->ray->direction, t);
	plane1 = init_plane(get_point(cy->center, cy->normal, cy->height / 2), cy->normal);
	plane2 = init_plane(get_point(cy->center, vector_mul(cy->normal, -1), cy->height / 2), vector_mul(cy->normal, -1));
	t3 = check_cylinder_base(plane1, inter, cy->normal);
	t4 = check_cylinder_base(plane2, inter, vector_mul(cy->normal, -1));
	if (t3 >= 0 && t3 <= cy->height && t4 >= 0 && t4 <= cy->height)
	{
		intersec->shape = cy;
		intersec->t = t;
		intersec->normal = cylinder_normal(inter, cy, t3);
	}
	find_cylinder_base(intersec, cy, plane1);
	find_cylinder_base(intersec, cy, plane2);
	return (0);
}
