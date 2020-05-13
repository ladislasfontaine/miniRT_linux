/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:08 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/13 18:00:49 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data	*init_window(t_scene *scene)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->mlx_ptr = mlx_init()))
	{
		ft_putstr("Error\nCannot initialize the minilibX\n");
		return (NULL);
	}
	if ((data->mlx_win = mlx_new_window(data->mlx_ptr,
		scene->resolution->w, scene->resolution->h, "miniRT")) == NULL)
	{
		ft_putstr("Error\nCannot create a new window\n");
		return (NULL);
	}
	return (data);
}

void	color_window(t_scene *scene)
{
	int			i;
	int			j;
	float		u;
	float		v;
	t_intersec	*intersec;

	j = 0;
	while (j < scene->resolution->h)
	{
		i = 0;
		while (i < scene->resolution->w)
		{
			u = (2.0f * i) / (float)scene->resolution->w - 1.0f;
			v = (-2.0f * j) / (float)scene->resolution->h + 1.0f;
			intersec = init_intersection(make_ray(scene, (t_camera *)scene->cameras->content, u, v));
			check_all_shapes(scene->shapes, intersec);
			if (intersected(intersec))
			{
				check_all_lights(scene, intersec);
				mlx_pixel_put(scene->window->mlx_ptr, scene->window->mlx_win, i, j, rgb_to_int(intersec->color));
			}
			else
				mlx_pixel_put(scene->window->mlx_ptr, scene->window->mlx_win, i, j, 0);
			clear_intersection(intersec);
			i++;
		}
		j++;
	}
}

void	check_all_shapes(t_list *shapes, t_intersec *intersec)
{
	t_shape	*shape;
	t_list	*lst_cpy;

	lst_cpy = shapes;
	while (lst_cpy)
	{
		shape = (t_shape *)(lst_cpy->content);
		if (shape->id == PLANE)
			plane_intersection(intersec, shape);
		else if (shape->id == SPHERE)
			sphere_intersection(intersec, shape);
		else if (shape->id == SQUARE)
			square_intersection(intersec, shape);
		else if (shape->id == TRIANGLE)
			triangle_intersection(intersec, shape);
		lst_cpy = lst_cpy->next;
	}
}
