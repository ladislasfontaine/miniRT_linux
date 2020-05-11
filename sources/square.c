/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:55 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 10:20:57 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** make it work with any normal vector square
** add normal vector for each side of the square
*/

int		square_intersection(t_intersec *intersec, t_shape *square)
{
	t_vector	*v_min;
	t_vector	*v_max;
	float		t0x;
	float		t1x;
	float		t0y;
	float		t1y;
	float		t0z;
	float		t1z;
	float		t_min;
	float		t_max;
	float		temp;
	
	v_min = init_vector(square->center->x - (square->side / 2.0), square->center->y - (square->side / 2.0), square->center->z - (square->side / 2.0));
	v_max = init_vector(square->center->x + (square->side / 2.0), square->center->y + (square->side / 2.0), square->center->z + (square->side / 2.0));
	// v_min->x == B0x dans le cours
	// 6 t car il y a 6 planes pour faire un carré
	t0x = (v_min->x - intersec->ray->origin->x) / intersec->ray->direction->x;
	t0y = (v_min->y - intersec->ray->origin->y) / intersec->ray->direction->y;
	t0z = (v_min->z - intersec->ray->origin->z) / intersec->ray->direction->z;
	t1x = (v_max->x - intersec->ray->origin->x) / intersec->ray->direction->x;
	t1y = (v_max->y - intersec->ray->origin->y) / intersec->ray->direction->y;
	t1z = (v_max->z - intersec->ray->origin->z) / intersec->ray->direction->z;

	if (t0x > t1x)
	{
		temp = t0x;
		t0x = t1x;
		t1x = temp;
	}
	if (t0y > t1y)
	{
		temp = t0y;
		t0y = t1y;
		t1y = temp;
	}
	if (t0z > t1z)
	{
		temp = t0z;
		t0z = t1z;
		t1z = temp;
	}

	t_min = (t0x > t0y) ? t0x : t0y;
	t_min = (t_min > t0z) ? t_min : t0z;
	t_max = (t1x < t1y) ? t1x : t1y;
	t_max = (t_max < t1z) ? t_max : t1z;

	if (t_min > t_max)//t0x > t1y || t0y > t1x || t0x > t1z || t0y > t1z || t0z > t1y || t0z > t1x) 
    	return (-1);
	if (t_min > RAY_MIN && t_min < intersec->t)
		intersec->t = t_min;
	else if (t_max > RAY_MIN && t_max < intersec->t)
		intersec->t = t_max;
	else
		return (0);
	intersec->shape = square;
	intersec->normal = init_vector(0, 1, 0);

	return (0);
}
