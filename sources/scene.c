/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:20:19 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 10:20:25 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*init_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	if (!(scene->resolution = (t_resolution *)malloc(sizeof(t_resolution))))
		return (NULL);
	scene->resolution->w = 0;
	scene->resolution->h = 0;
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
	scene->window = NULL;
	return (scene);
}

void	clear_scene(t_scene *scene)
{
	// check each element and free it if not NULL
	if (scene)
		free(scene);
}
