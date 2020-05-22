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
	float		a;
	float		b;
	float		t1;
	float		t2;
	t_vector	*d;

	a = dot_product(vector_diff(intersec->ray->origin, sq->center), sq->normal);
	b = dot_product(intersec->ray->direction, sq->normal);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t1 = -a / b;
	d = vector_diff(vector_add(vector_mul(intersec->ray->direction, t1),
			intersec->ray->origin), sq->center);
	t2 = sq->side / 2;
	if (fabs(d->x) > t2 || fabs(d->y) > t2 || fabs(d->z) > t2)
		return (0);
	if (t1 > RAY_MIN && t1 < intersec->t)
		intersec->t = t1;
	else
		return (0);
	intersec->shape = sq;
	intersec->normal = (get_angle(intersec->ray->direction, sq->normal) < 90.0)
						? vector_mul(sq->normal, -1) : sq->normal;
	return (0);
}

t_shape		*init_square(t_vector *c, t_vector *n, float side, t_color *color)
{
	t_shape	*new;

	new = (t_shape *)malloc(sizeof(t_shape));
	if (!new)
		return (NULL);
	new->id = SQUARE;
	new->side = side;
	new->center = init_vector(c->x, c->y, c->z);
	new->normal = init_vector(n->x, n->y, n->z);
	new->color = init_color(color->r, color->g, color->b);
	if (!new->center || !new->normal || !new->color)
	{
		if (new->center)
			free(new->center);
		if (new->normal)
			free(new->normal);
		if (new->color)
			free(new->color);
		free(new);
		return (NULL);
	}
	return (new);
}
