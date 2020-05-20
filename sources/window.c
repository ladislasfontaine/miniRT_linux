/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:08 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 10:49:38 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *scene)
{
	if (!(scene->win = (t_data *)malloc(sizeof(t_data))))
		error_and_quit(scene, "Malloc failed");
	if (!(scene->win->mlx_ptr = mlx_init()))
		error_and_quit(scene, "Cannot initialize the minilibX");
	scene->win->img_id = 0;
}

void	init_window(t_scene *scene)
{
	if ((scene->win->mlx_win = mlx_new_window(scene->win->mlx_ptr,
		scene->res->w, scene->res->h, "miniRT")) == NULL)
		error_and_quit(scene, "Failed to create a new window");
}

int		color_image(t_scene *scene, t_camera *camera,t_img *img)
{
	float		u;
	float		v;
	int			i;
	int			j;
	int			k;
	t_intersec	*intersec;

	img->data = mlx_get_data_addr(img->mlx_img, &img->bpp, &img->size_line, &img->endian);
	k = 0;
	j = 0;
	while (j < scene->res->h)
	{
		i = 0;
		while (i < scene->res->w)
		{
			u = (2.0f * i) / (float)scene->res->w - 1.0f;
			v = (-2.0f * j) / (float)scene->res->h + 1.0f;
			intersec = init_intersection(make_ray(scene, camera, u, v));
			check_all_shapes(scene->shapes, intersec);
			if (intersected(intersec))
			{
				add_ambient_light(scene, intersec);
				check_all_lights(scene, intersec);
			}
			img->data[k] = (intersected(intersec)) ? intersec->color->b : 0;
			img->data[k + 1] = (intersected(intersec)) ? intersec->color->g : 0;
			img->data[k + 2] = (intersected(intersec)) ? intersec->color->r : 0;
			img->data[k + 3] = 0;
			k += 4;
			clear_intersection(intersec);
			i++;
		}
		j++;
	}
	return (0);
}

void	create_images(t_scene *sc)
{
	t_list	*cameras;
	t_img	*img;

	cameras = sc->cameras;
	while (cameras)
	{
		img = NULL;
		if (!(img = init_image(sc)))
			error_and_quit(sc, "Cannot initialize the minilibX image");
		if (!(img->mlx_img = mlx_new_image(sc->win->mlx_ptr, sc->res->w, sc->res->h)))
			error_and_quit(sc, "Malloc for new image failed");
		color_image(sc, (t_camera *)cameras->content, img);
		ft_lstadd_back(&sc->imgs, ft_lstnew((void *)img));
		cameras = cameras->next;
	}
	if (!sc->save)
		mlx_put_image_to_window(sc->win->mlx_ptr, sc->win->mlx_win, ((t_img *)(sc->imgs->content))->mlx_img, 0, 0);
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
