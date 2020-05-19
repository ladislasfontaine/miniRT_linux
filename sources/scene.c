/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:19 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 14:47:05 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*init_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	if (!(scene->res = (t_resolution *)malloc(sizeof(t_resolution))))
		return (NULL);
	scene->res->w = 0;
	scene->res->h = 0;
	if (!(scene->ambient = (t_ambient *)malloc(sizeof(t_ambient))))
		return (NULL);
	scene->ambient->ratio = -1;
	if (!(scene->ambient->color = (t_color *)malloc(sizeof(t_color))))
		return (NULL);
	scene->ambient->color->r = -1;
	scene->ambient->color->g = -1;
	scene->ambient->color->b = -1;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->shapes = NULL;
	scene->win = NULL;
	return (scene);
}

void	delete_shape(void *element)
{
	t_shape	*shape;

	shape = (t_shape *)element;
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
	if (shape)
		free(shape);
}

void	delete_camera(void *element)
{
	t_camera	*camera;

	camera = (t_camera *)element;
	if (camera->origin)
		free(camera->origin);
	if (camera->direction)
		free(camera->direction);
	if (camera->up)
		free(camera->up);
	if (camera->right)
		free(camera->right);
	if (camera)
		free(camera);
}

void	delete_light(void *element)
{
	t_light	*light;

	light = (t_light *)element;
	if (light->origin)
		free(light->origin);
	if (light->color)
		free(light->color);
	if (light)
		free(light);
}

void	clear_scene(t_scene *scene)
{
	if (scene->res)
		free(scene->res);
	if (scene->ambient->color)
		free(scene->ambient->color);
	if (scene->ambient)
		free(scene->ambient);
	ft_lstclear(&scene->shapes, &delete_shape);
	ft_lstclear(&scene->cameras, &delete_camera);
	ft_lstclear(&scene->lights, &delete_light);
	if (scene)
		free(scene);
}
