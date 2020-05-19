/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:34 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 10:41:19 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_resolution(char *line, t_scene *scene, int n)
{
	int	i;

	i = 0;
	if (scene->resolution->w != 0 || scene->resolution->h != 0)
	{
		ft_printf("Error\nLine %d. Resolution can only be declared once\n", n);
		return (-1);
	}
	i += is_space(line + i);
	i += parse_int(line + i, &scene->resolution->w);
	i += is_space(line + i);
	i += parse_int(line + i, &scene->resolution->h);
	i += is_space(line + i);
	if (scene->resolution->w == -1 || scene->resolution->h == -1 || line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the resolution line\n", n);
		return (-1);
	}
	else if (scene->resolution->w <= 0 || scene->resolution->h <= 0)
	{
		ft_printf("Error\nLine %d. ", n);
		ft_printf("Resolution sizes should be greater than zero\n");
		return (-1);
	}
	return (0);
}

int		parse_ambient(char *line, t_scene *scene, int n)
{
	int	i;

	i = 0;
	if (scene->ambient->ratio != -1 || scene->ambient->color->r != -1)
	{
		ft_printf("Error\nLine %d. Ambient light declared more than once\n", n);
		return (-1);
	}
	i += is_space(line + i);
	i += parse_float(line + i, &scene->ambient->ratio);
	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0)
	{
		ft_printf("Error\nLine %d. Ambient ratio not in range 0.0 to 1.0\n", n);
		return (-1);
	}
	i += is_space(line + i);
	i += parse_color(line + i, scene->ambient->color);
	i += is_space(line + i);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem in the ambient lightning line\n", n);
		return (-1);
	}
	if (check_color_range(scene->ambient->color, n) == -1)
		return (-1);
	return (0);
}

int		parse_camera(char *line, t_scene *scene, int n)
{
	t_camera	*camera;
	t_vector	*upguide;
	int			i;

	camera = init_camera_null();
	ft_lstadd_back(&scene->cameras, ft_lstnew((void *)camera));
	camera = (t_camera *)(ft_lstlast(scene->cameras)->content);
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, camera->origin);
	i += is_space(line + i);
	i += parse_vector(line + i, camera->direction);
	i += is_space(line + i);
	i += parse_float(line + i, &camera->fov);
	i += is_space(line + i);
	if (!(upguide = init_vector(0.0, 1.0, 0.0)))
		return (-1);
	normalize(camera->direction);
	// working if camera direction is 0,1,0 ?
	camera->right = cross_product(camera->direction, upguide);
	normalize(camera->right);
	camera->up = cross_product(camera->right, camera->direction);
	free(upguide);
	if (camera->fov < 0.0 || camera->fov > 180.0)
	{
		ft_printf("Error\nLine %d. FOV not in range 0 to 180 degrees\n", n);
		return (-1);
	}
	if (check_normal_vector(camera->direction, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the camera line\n", n);
		return (-1);
	}
	return (0);
}

int		parse_light(char *line, t_scene *scene, int n)
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
	{
		ft_printf("Error\nLine %d. Brightness not in range 0.0 to 1.0\n", n);
		return (-1);
	}
	if (check_color_range(light->color, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the light line\n", n);
		return (-1);
	}
	return (0);
}
