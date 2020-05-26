/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:01 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 15:48:01 by lafontai         ###   ########.fr       */
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

t_vector	*malloc_vector(t_vector vec)
{
	t_vector	*new;

	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	new->x = vec.x;
	new->y = vec.y;
	new->z = vec.z;
	return (new);
}

void		copy_vector(t_vector *dest, t_vector src)
{
	dest->x = src.x;
	dest->y = src.y;
	dest->z = src.z;
}

t_vector	get_point(t_vector origin, t_vector dir, float t)
{
	t_vector	point;

	point.x = origin.x + t * dir.x;
	point.y = origin.y + t * dir.y;
	point.z = origin.z + t * dir.z;
	return (point);
}

void		check_normal_vector(t_scene *scene, t_vector *u)
{
	if (u->x < -1.0 || u->x > 1.0 || u->y < -1.0 || u->y > 1.0 ||
		u->z < -1.0 || u->z > 1.0)
		error_and_quit(scene, "Problem with the normalized vector");
	normalize(u);
}
