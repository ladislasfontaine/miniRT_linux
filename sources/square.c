/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:55 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/13 16:07:57 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		square_intersection(t_intersec *intersec, t_shape *square)
{
	float		a;
	float		b;
	float		t1;
	float		t2;
	t_vector	*d;

	a = dot_product(vector_diff(intersec->ray->origin, square->center), square->normal);
	b = dot_product(intersec->ray->direction, square->normal);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t1 = -a / b;
	d = vector_diff(vector_add(vector_mul(intersec->ray->direction, t1), intersec->ray->origin), square->center);
	t2 = square->side / 2;
	if (fabs(d->x) > t2 || fabs(d->y) > t2 || fabs(d->z) > t2)
		return (0);
	if (t1 > RAY_MIN && t1 < intersec->t)
		intersec->t = t1;
	else
		return (0);
	intersec->shape = square;
	intersec->normal = square->normal;
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

int		square_sides(t_scene *scene, t_vector *center, float s, t_color *c)
{
	t_shape		*square;
	
	if ((square = init_square(&(t_vector){center->x, center->y,
		center->z + s / 2}, &(t_vector){0, 0, 1}, s, c)))
		ft_lstadd_back(&scene->shapes, ft_lstnew((void *)square));
	if ((square = init_square(&(t_vector){center->x, center->y,
		center->z - s / 2}, &(t_vector){0, 0, 1}, s, c)))
		ft_lstadd_back(&scene->shapes, ft_lstnew((void *)square));
	if ((square = init_square(&(t_vector){center->x, center->y + s / 2,
		center->z}, &(t_vector){0, 1, 0}, s, c)))
		ft_lstadd_back(&scene->shapes, ft_lstnew((void *)square));
	if ((square = init_square(&(t_vector){center->x, center->y - s / 2,
		center->z}, &(t_vector){0, 1, 0}, s, c)))
		ft_lstadd_back(&scene->shapes, ft_lstnew((void *)square));
	if ((square = init_square(&(t_vector){center->x + s / 2, center->y,
		center->z}, &(t_vector){1, 0, 0}, s, c)))
		ft_lstadd_back(&scene->shapes, ft_lstnew((void *)square));
	if ((square = init_square(&(t_vector){center->x - s / 2, center->y,
		center->z}, &(t_vector){1, 0, 0}, s, c)))
		ft_lstadd_back(&scene->shapes, ft_lstnew((void *)square));
	return (0);
}
