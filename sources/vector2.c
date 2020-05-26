/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:24:56 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 15:25:44 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float		square(float x)
{
	return (x * x);
}

float		length_square(t_vector u)
{
	return (square(u.x) + square(u.y) + square(u.z));
}

float		length(t_vector u)
{
	return (sqrt(length_square(u)));
}

float		normalize(t_vector *u)
{
	double	len;

	len = length(*u);
	u->x = u->x / len;
	u->y = u->y / len;
	u->z = u->z / len;
	return (len);
}

float		dot_product(t_vector u, t_vector v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}
