/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:18:46 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 09:40:51 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		camera_vector_calculation(t_scene *scene, t_camera *cam)
{
	normalize(cam->direction);
	if (cam->direction->x == 0 && cam->direction->z == 0
		&& (cam->direction->y == 1 || cam->direction->y == -1))
		*cam->right = cross_product(*cam->direction, (t_vector){-1, 0, 0});
	else
		*cam->right = cross_product(*cam->direction, (t_vector){0, 1, 0});
	normalize(cam->right);
	*cam->up = cross_product(*cam->right, *cam->direction);
	if (cam->fov < 0.0 || cam->fov > 180.0)
		error_and_quit(scene, "FOV not in range 0 to 180 degrees");
}

t_camera	*init_camera_null(void)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	if (!((camera->origin = (t_vector *)malloc(sizeof(t_vector))) &&
		(camera->direction = (t_vector *)malloc(sizeof(t_vector))) &&
		(camera->up = (t_vector *)malloc(sizeof(t_vector))) &&
		(camera->right = (t_vector *)malloc(sizeof(t_vector)))))
		return (NULL);
	camera->fov = 0;
	return (camera);
}

void		clear_camera(t_camera *cam)
{
	if (cam)
	{
		if (cam->origin)
			free(cam->origin);
		if (cam->direction)
			free(cam->direction);
		if (cam->up)
			free(cam->up);
		if (cam->right)
			free(cam->right);
		free(cam);
	}
}

t_ray		*make_ray(t_scene *scene, t_camera *cam, float u, float v)
{
	t_vector	*origin;
	t_vector	*dir;
	float		w;
	float		h;

	h = tan(cam->fov / 180.0);
	w = h * ((float)scene->res->w / (float)scene->res->h);
	origin = init_vector(cam->origin->x, cam->origin->y, cam->origin->z);
	if (!origin)
		error_and_quit(scene, "Malloc failed");
	if (!(dir = (t_vector *)malloc(sizeof(t_vector))))
	{
		free(origin);
		error_and_quit(scene, "Malloc failed");
	}
	dir->x = cam->direction->x + u * w * cam->right->x + v * h * cam->up->x;
	dir->y = cam->direction->y + u * w * cam->right->y + v * h * cam->up->y;
	dir->z = cam->direction->z + u * w * cam->right->z + v * h * cam->up->z;
	normalize(dir);
	return (init_ray(origin, dir, RAY_MAX));
}

int			change_camera(t_scene *scene, int id)
{
	t_data	*w;
	t_list	*img;
	int		i;

	w = scene->win;
	if (id < 0)
		scene->win->img_id = ft_lstsize(scene->imgs) + id;
	else if (id > ft_lstsize(scene->imgs) - 1)
		scene->win->img_id = id % ft_lstsize(scene->imgs);
	else
		scene->win->img_id = id;
	img = scene->imgs;
	i = 0;
	while (img && i < scene->win->img_id)
	{
		img = img->next;
		i++;
	}
	mlx_put_image_to_window(w->mlx_ptr, w->mlx_win,
			((t_image *)(img->content))->mlx_img, 0, 0);
	return (0);
}
