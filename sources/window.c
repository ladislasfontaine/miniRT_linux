/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:08 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 14:52:05 by lafontai         ###   ########.fr       */
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
		scene->res->w, scene->res->h, "miniRT")) == NULL)
	{
		ft_putstr("Error\nCannot create a new window\n");
		return (NULL);
	}
	return (data);
}

int		color_image(t_scene *scene)
{
	char		*data;
	float		u;
	float		v;
	int			i;
	int			j;
	int			k;
	t_intersec	*intersec;
	t_img		*img;

	img = scene->win->img;
	data = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->size_line, &img->endian);
	k = 0;
	j = 0;
	while (j < scene->res->h)
	{
		i = 0;
		while (i < scene->res->w)
		{
			u = (2.0f * i) / (float)scene->res->w - 1.0f;
			v = (-2.0f * j) / (float)scene->res->h + 1.0f;
			intersec = init_intersection(make_ray(scene, (t_camera *)scene->cameras->content, u, v));
			check_all_shapes(scene->shapes, intersec);
			if (intersected(intersec))
			{
				add_ambient_light(scene, intersec);
				check_all_lights(scene, intersec);
			}
			data[k] = (intersected(intersec)) ? intersec->color->b : 0;
			data[k + 1] = (intersected(intersec)) ? intersec->color->g : 0;
			data[k + 2] = (intersected(intersec)) ? intersec->color->r : 0;
			data[k + 3] = 0;
			k += 4;
			clear_intersection(intersec);
			i++;
		}
		j++;
	}
	return (0);
}

int		create_images(t_scene *sc)
{
	t_data	*w;

	w = sc->win;
	// while cameras on crée une nouvelle image
	if (!(w->img = init_image(sc)))
	{
		ft_printf("Error\nCannot initialize the minilibX image\n");
		return (-1);
	}
	w->img->mlx_img = mlx_new_image(w->mlx_ptr, sc->res->w, sc->res->h);
	color_image(sc);

	// select an image
	mlx_put_image_to_window(w->mlx_ptr, w->mlx_win, w->img->mlx_img, 0, 0);
	return (0);
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
		else if (shape->id == CYLINDER)
			cylinder_intersection(intersec, shape);
		lst_cpy = lst_cpy->next;
	}
}
