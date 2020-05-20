/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:34 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 14:34:05 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_resolution(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->res->w != 0 || scene->res->h != 0)
		error_and_quit(scene, "Resolution can only be declared once");
	i += is_space(line + i);
	i += parse_int(line + i, &scene->res->w);
	i += is_space(line + i);
	i += parse_int(line + i, &scene->res->h);
	i += is_space(line + i);
	if (scene->res->w == -1 || scene->res->h == -1 || line[i])
		error_and_quit(scene, "Problem parsing the resolution line");
	else if (scene->res->w <= 0 || scene->res->h <= 0)
		error_and_quit(scene, "Resolution sizes should be greater than zero");
	return (0);
}

int		parse_ambient(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->ambient->ratio != -1 || scene->ambient->color->r != -1)
		error_and_quit(scene, "Ambient light declared more than once");
	i += is_space(line + i);
	i += parse_float(line + i, &scene->ambient->ratio);
	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0)
		error_and_quit(scene, "Ambient ratio not in range 0.0 to 1.0");
	i += is_space(line + i);
	i += parse_color(line + i, scene->ambient->color);
	i += is_space(line + i);
	if (line[i])
		error_and_quit(scene, "Problem in the ambient lightning line");
	check_color_range(scene, scene->ambient->color);
	return (0);
}

int		parse_camera(char *line, t_scene *scene)
{
	t_camera	*camera;
	t_list		*element;
	int			i;

	if (!(camera = init_camera_null()))
	{
		clear_camera(camera);
		error_and_quit(scene, "Malloc failed");
	}
	if (!(element = ft_lstnew((void *)camera)))
		error_and_quit(scene, "Malloc failed");
	ft_lstadd_back(&scene->cameras, element);
	camera = (t_camera *)(ft_lstlast(scene->cameras)->content);
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, camera->origin);
	i += is_space(line + i);
	i += parse_vector(line + i, camera->direction);
	i += is_space(line + i);
	i += parse_float(line + i, &camera->fov);
	i += is_space(line + i);
	camera_vector_calculation(scene, camera);
	if (line[i])
		error_and_quit(scene, "Problem parsing the camera line");
	return (0);
}

int		parse_light(char *line, t_scene *scene)
{
	t_light		*light;
	int			i;

	light = init_light_null();
	ft_lstadd_back(&scene->lights, ft_lstnew((void *)light));
	light = (t_light *)(ft_lstlast(scene->lights)->content);
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, light->origin);
	i += is_space(line + i);
	i += parse_float(line + i, &light->brightness);
	i += is_space(line + i);
	i += parse_color(line + i, light->color);
	i += is_space(line + i);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		error_and_quit(scene, "Brightness not in range 0.0 to 1.0");
	check_color_range(scene, light->color);
	if (line[i])
		error_and_quit(scene, "Problem parsing the light line");
	return (0);
}
