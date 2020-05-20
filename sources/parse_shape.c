/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:42 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 10:32:12 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_sphere(char *line, t_scene *scene)
{
	t_shape		*shape;
	int			i;

	shape = init_shape();
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)shape));
	shape = (t_shape *)(ft_lstlast(scene->shapes)->content);
	shape->id = SPHERE;
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, shape->center);
	i += is_space(line + i);
	i += parse_float(line + i, &shape->diameter);
	i += is_space(line + i);
	i += parse_color(line + i, shape->color);
	i += is_space(line + i);
	check_color_range(scene, shape->color);
	if (line[i])
		error_and_quit(scene, "Problem parsing the sphere line");
	return (0);
}

int		parse_plane(char *line, t_scene *scene)
{
	t_shape		*shape;
	int			i;

	shape = init_shape();
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)shape));
	shape = (t_shape *)(ft_lstlast(scene->shapes)->content);
	shape->id = PLANE;
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, shape->position);
	i += is_space(line + i);
	i += parse_vector(line + i, shape->normal);
	i += is_space(line + i);
	i += parse_color(line + i, shape->color);
	i += is_space(line + i);
	check_color_range(scene, shape->color);
	check_normal_vector(scene, shape->normal);
	if (line[i])
		error_and_quit(scene, "Problem parsing the plane line");
	return (0);
}

int		parse_square(char *line, t_scene *scene)
{
	t_shape		*shape;
	int			i;

	shape = init_shape();
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)shape));
	shape = (t_shape *)(ft_lstlast(scene->shapes)->content);
	shape->id = SQUARE;
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, shape->center);
	i += is_space(line + i);
	i += parse_vector(line + i, shape->normal);
	i += is_space(line + i);
	i += parse_float(line + i, &shape->side);
	i += is_space(line + i);
	i += parse_color(line + i, shape->color);
	i += is_space(line + i);
	check_color_range(scene, shape->color);
	check_normal_vector(scene, shape->normal);
	if (line[i])
		error_and_quit(scene, "Problem parsing the square line");
	//square_sides(scene, center, side, color);
	return (0);
}

int		parse_cylinder(char *line, t_scene *scene)
{
	t_shape		*shape;
	int			i;

	shape = init_shape();
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)shape));
	shape = (t_shape *)(ft_lstlast(scene->shapes)->content);
	shape->id = CYLINDER;
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, shape->center);
	i += is_space(line + i);
	i += parse_vector(line + i, shape->normal);
	i += is_space(line + i);
	i += parse_float(line + i, &shape->diameter);
	i += is_space(line + i);
	i += parse_float(line + i, &shape->height);
	i += is_space(line + i);
	i += parse_color(line + i, shape->color);
	i += is_space(line + i);
	check_color_range(scene, shape->color);
	check_normal_vector(scene, shape->normal);
	if (line[i])
		error_and_quit(scene, "Problem parsing the cylinder line");
	return (0);
}

int		parse_triangle(char *line, t_scene *scene)
{
	t_shape		*shape;
	int			i;

	shape = init_shape();
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)shape));
	shape = (t_shape *)(ft_lstlast(scene->shapes)->content);
	shape->id = TRIANGLE;
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, shape->p1);
	i += is_space(line + i);
	i += parse_vector(line + i, shape->p2);
	i += is_space(line + i);
	i += parse_vector(line + i, shape->p3);
	i += is_space(line + i);
	i += parse_color(line + i, shape->color);
	i += is_space(line + i);
	check_color_range(scene, shape->color);
	if (line[i])
		error_and_quit(scene, "Problem parsing the triangle line");
	return (0);
}
