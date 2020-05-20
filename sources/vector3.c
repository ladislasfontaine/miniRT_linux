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
