/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:19 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/22 09:19:38 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*init_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		error_and_quit(scene, "Malloc failed");
	if (!(scene->res = (t_resolution *)malloc(sizeof(t_resolution))))
		error_and_quit(scene, "Malloc failed");
	scene->res->w = 0;
	scene->res->h = 0;
	if (!(scene->ambient = (t_ambient *)malloc(sizeof(t_ambient))))
		error_and_quit(scene, "Malloc failed");
	scene->ambient->ratio = -1;
	if (!(scene->ambient->color = (t_color *)malloc(sizeof(t_color))))
		error_and_quit(scene, "Malloc failed");
	scene->ambient->color->r = -1;
	scene->ambient->color->g = -1;
	scene->ambient->color->b = -1;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->shapes = NULL;
	scene->imgs = NULL;
	scene->win = NULL;
	scene->save = 0;
	return (scene);
}

void	clear_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->res)
			free(scene->res);
		if (scene->ambient)
		{
			if (scene->ambient->color)
				free(scene->ambient->color);
			free(scene->ambient);
		}
		ft_lstclear(&scene->shapes, &delete_shape);
		ft_lstclear(&scene->cameras, &delete_camera);
		ft_lstclear(&scene->lights, &delete_light);
		delete_images(&scene->imgs, scene);
		free(scene);
	}
}
