/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:42 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/15 12:29:19 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_sphere(char *line, t_scene *scene, int n)
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
	if (check_color_range(shape->color, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the sphere line\n", n);
		return (-1);
	}
	return (0);
}

int		parse_plane(char *line, t_scene *scene, int n)
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
	if (check_color_range(shape->color, n) == -1)
		return (-1);
	if (check_normal_vector(shape->normal, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the plane line\n", n);
		return (-1);
	}
	return (0);
}

int		parse_square(char *line, t_scene *scene, int n)
{
	t_vector	*center;
	t_vector	*normal;
	t_color		*color;
	float		side;
	int			i;

	center = (t_vector *)malloc(sizeof(t_vector));
	normal = (t_vector *)malloc(sizeof(t_vector));
	color = (t_color *)malloc(sizeof(t_color));
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, center);
	i += is_space(line + i);
	i += parse_vector(line + i, normal);
	i += is_space(line + i);
	i += parse_float(line + i, &side);
	i += is_space(line + i);
	i += parse_color(line + i, color);
	i += is_space(line + i);
	if (check_color_range(color, n) == -1)
		return (-1);
	if (check_normal_vector(normal, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the square line\n", n);
		return (-1);
	}
	square_sides(scene, center, side, color);
	return (0);
}

int		parse_cylinder(char *line, t_scene *scene, int n)
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
	if (check_color_range(shape->color, n) == -1)
		return (-1);
	if (check_normal_vector(shape->normal, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the cylinder line\n", n);
		return (-1);
	}
	return (0);
}

int		parse_triangle(char *line, t_scene *scene, int n)
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
	if (check_color_range(shape->color, n) == -1)
		return (-1);
	if (line[i])
	{
		ft_printf("Error\nLine %d. Problem parsing the triangle line\n", n);
		return (-1);
	}
	return (0);
}
