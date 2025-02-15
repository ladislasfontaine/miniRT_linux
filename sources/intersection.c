/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:11 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 11:44:04 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*init_intersection(t_ray *ray)
{
	t_intersec	*new;

	if (!(new = (t_intersec *)malloc(sizeof(t_intersec))))
		return (NULL);
	new->ray = ray;
	new->shape = NULL;
	new->t = ray->max_t;
	if (!(new->color = init_color(0, 0, 0)) ||
		!(new->normal = (t_vector *)malloc(sizeof(t_vector))))
	{
		if (new->color)
			free(new->color);
		if (new->normal)
			free(new->normal);
		free(new);
		return (NULL);
	}
	return (new);
}

int			intersected(t_intersec *intersec)
{
	if (!intersec->shape)
		return (0);
	return (1);
}

t_vector	*intersection(t_intersec *intersec)
{
	return (point_on_ray(*(intersec->ray), intersec->t));
}

void		clear_intersection(t_intersec *intersec)
{
	if (intersec)
	{
		if (intersec->ray)
		{
			if (intersec->ray->origin)
				free(intersec->ray->origin);
			if (intersec->ray->direction)
				free(intersec->ray->direction);
			free(intersec->ray);
		}
		if (intersec->color)
			free(intersec->color);
		if (intersec->normal)
			free(intersec->normal);
		free(intersec);
	}
}
