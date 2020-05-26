/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:31 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 10:20:34 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape		*init_shape(void)
{
	t_shape	*new;

	new = (t_shape *)malloc(sizeof(t_shape));
	if (!new)
		return (NULL);
	new->id = 1;
	new->diameter = 0.0;
	new->height = 0.0;
	new->side = 0.0;
	if (!((new->center = (t_vector *)malloc(sizeof(t_vector))) &&
		(new->position = (t_vector *)malloc(sizeof(t_vector))) &&
		(new->normal = (t_vector *)malloc(sizeof(t_vector))) &&
		(new->p1 = (t_vector *)malloc(sizeof(t_vector))) &&
		(new->p2 = (t_vector *)malloc(sizeof(t_vector))) &&
		(new->p3 = (t_vector *)malloc(sizeof(t_vector))) &&
		(new->color = (t_color *)malloc(sizeof(t_color)))))
	{
		clear_shape(new);
		return (NULL);
	}
	new->color->r = -1;
	return (new);
}

void		clear_shape(t_shape *shape)
{
	if (shape)
	{
		if (shape->center)
			free(shape->center);
		if (shape->position)
			free(shape->position);
		if (shape->normal)
			free(shape->normal);
		if (shape->p1)
			free(shape->p1);
		if (shape->p2)
			free(shape->p2);
		if (shape->p3)
			free(shape->p3);
		if (shape->color)
			free(shape->color);
		free(shape);
	}
}
