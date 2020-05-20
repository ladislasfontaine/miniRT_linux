/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:01 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 15:26:15 by lafontai         ###   ########.fr       */
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
