/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:01 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 10:22:20 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	*init_vector(float x, float y, float z)
{
	t_vector	*new;

	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_vector	*get_point(t_vector *origin, t_vector *dir, float t)
{
	t_vector	*point;
	float		x;
	float		y;
	float		z;

	x = origin->x + t * dir->x;
	y = origin->y + t * dir->y;
	z = origin->z + t * dir->z;
	point = init_vector(x, y, z);
	return (point);
}

float		square(float x)
{
	return (x * x);
}

float		length_square(t_vector *u)
{
	return (square(u->x) + square(u->y) + square(u->z));
}

float		length(t_vector *u)
{
	return (sqrt(length_square(u)));
}

float		normalize(t_vector *u)
{
	double	len;

	len = length(u);
	u->x = u->x / len;
	u->y = u->y / len;
	u->z = u->z / len;
	return (len);
}

float		dot_product(t_vector *u, t_vector *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

t_vector	*cross_product(t_vector *u, t_vector *v)
{
	return (init_vector(((u->y * v->z) - (u->z * v->y)),
		((u->z * v->x) - (u->x * v->z)),
		((u->x * v->y) - (u->y * v->x))));
}

t_vector	*vector_diff(t_vector *u, t_vector *v)
{
	return (init_vector(u->x - v->x, u->y - v->y, u->z - v->z));
}

t_vector	*vector_add(t_vector *u, t_vector *v)
{
	return (init_vector(u->x + v->x, u->y + v->y, u->z + v->z));
}

t_vector	*vector_mul(t_vector *u, float n)
{
	return (init_vector(u->x * n, u->y * n, u->z * n));
}

void		check_normal_vector(t_scene *scene, t_vector *u)
{
	if (u->x < -1.0 || u->x > 1.0 || u->y < -1.0 || u->y > 1.0 ||
		u->z < -1.0 || u->z > 1.0)
		error_and_quit(scene, "Problem with the normalized vector");
}

float		get_angle(t_vector *u, t_vector *v)
{
	float	angle;

	angle = acos((dot_product(u, v) / (length(u) * length(v))));
	return (angle * 180 / PI);
}
