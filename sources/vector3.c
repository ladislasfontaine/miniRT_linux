/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:25:09 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 15:26:12 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	cross_product(t_vector u, t_vector v)
{
	t_vector	vec;

	vec.x = (u.y * v.z) - (u.z * v.y);
	vec.y = (u.z * v.x) - (u.x * v.z);
	vec.z = (u.x * v.y) - (u.y * v.x);
	return (vec);
}

t_vector	vector_diff(t_vector u, t_vector v)
{
	t_vector	vec;

	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

t_vector	vector_add(t_vector u, t_vector v)
{
	t_vector	vec;

	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	vec.z = u.z + v.z;
	return (vec);
}

t_vector	vector_mul(t_vector u, float n)
{
	t_vector	vec;

	vec.x = u.x * n;
	vec.y = u.y * n;
	vec.z = u.z * n;
	return (vec);
}

float		get_angle(t_vector *u, t_vector *v)
{
	float	angle;

	angle = acos((dot_product(*u, *v) / (length(*u) * length(*v))));
	return (angle * 180 / PI);
}
