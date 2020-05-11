/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:18:46 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 15:41:11 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*init_camera(t_vector *origin, t_vector *orientation, float fov)
{
	t_vector	*upguide;
	t_camera	*new;

	new = (t_camera *)malloc(sizeof(t_camera));
	if (!new)
		return (NULL);
	if (!(upguide = init_vector(0.0, 1.0, 0.0)))
		return (NULL);
	new->origin = origin;
	new->direction = orientation;
	normalize(new->direction);
	new->fov = fov;
	new->right = cross_product(new->direction, upguide);
	normalize(new->right);
	new->up = cross_product(new->right, new->direction);
	free(upguide);
	return (new);
}

t_camera	*init_camera_null(void)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->origin = (t_vector *)malloc(sizeof(t_vector));
	camera->direction = (t_vector *)malloc(sizeof(t_vector));
	camera->up = (t_vector *)malloc(sizeof(t_vector));
	camera->right = (t_vector *)malloc(sizeof(t_vector));
	camera->fov = 0;
	return (camera);
}

t_ray		*make_ray(t_scene *scene, t_camera *cam, float u, float v)
{
	t_vector	*origin;
	t_vector	*dir;
	float		w;
	float		h;

	h = tan(cam->fov / 180.0);
	w = h * ((float)scene->resolution->w / (float)scene->resolution->h);
	origin = init_vector(cam->origin->x, cam->origin->y, cam->origin->z);
	if (!origin)
		return (NULL);
	dir = (t_vector *)malloc(sizeof(t_vector));
	if (!dir)
	{
		free(origin);
		return (NULL);
	}
	dir->x = cam->direction->x + u * w * cam->right->x + v * h * cam->up->x;
	dir->y = cam->direction->y + u * w * cam->right->y + v * h * cam->up->y;
	dir->z = cam->direction->z + u * w * cam->right->z + v * h * cam->up->z;
	normalize(dir);
	return (init_ray(origin, dir, RAY_MAX));
}
