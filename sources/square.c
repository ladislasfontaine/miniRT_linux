/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:55 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 16:04:01 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			square_intersection(t_intersec *intersec, t_shape *sq)
{
	t_vector	p;
	t_vector	t;
	t_vector	d;

	p.x = dot_product(vector_diff(*intersec->ray->origin, *sq->center),
			*sq->normal);
	p.y = dot_product(*intersec->ray->direction, *sq->normal);
	if (p.y == 0 || (p.x < 0 && p.y < 0) || (p.x > 0 && p.y > 0))
		return (0);
	t.x = -p.x / p.y;
	d = vector_diff(vector_add(vector_mul(*intersec->ray->direction, t.x),
			*intersec->ray->origin), *sq->center);
	t.y = sq->side / 2;
	if (fabs(d.x) > t.y || fabs(d.y) > t.y || fabs(d.z) > t.y)
		return (0);
	if (t.x > RAY_MIN && t.x < intersec->t)
		intersec->t = t.x;
	else
		return (0);
	intersec->shape = sq;
	if (get_angle(intersec->ray->direction, sq->normal) < 90.0)
		copy_vector(intersec->normal, vector_mul(*sq->normal, -1));
	else
		copy_vector(intersec->normal, *sq->normal);
	return (0);
}
