/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:21:08 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 11:53:15 by lafontai         ###   ########.fr       */
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
	check_window_size(scene);
}

void	init_window(t_scene *scene)
{
	if ((scene->win->mlx_win = mlx_new_window(scene->win->mlx_ptr,
		scene->res->w, scene->res->h, "miniRT")) == NULL)
		error_and_quit(scene, "Failed to create a new window");
}

int		check_all_shapes(t_list *shapes, t_intersec *intersec)
{
	t_shape	*shape;
	t_list	*lst_cpy;
	int		res;

	lst_cpy = shapes;
	while (lst_cpy)
	{
		shape = (t_shape *)(lst_cpy->content);
		if (shape->id == PLANE)
			res = plane_intersection(intersec, shape);
		else if (shape->id == SPHERE)
			res = sphere_intersection(intersec, shape);
		else if (shape->id == SQUARE)
			res = square_intersection(intersec, shape);
		else if (shape->id == TRIANGLE)
			res = triangle_intersection(intersec, shape);
		else if (shape->id == CYLINDER)
			res = cylinder_intersection(intersec, shape);
		if (res == -1)
			return (-1);
		lst_cpy = lst_cpy->next;
	}
	return (0);
}

void	check_window_size(t_scene *scene)
{
	int	x;
	int	y;

	if (!(mlx_get_screen_size(scene->win->mlx_ptr, &x, &y)))
		error_and_quit(scene, "Cannot get screen size");
	if (scene->res->w > x)
		scene->res->w = x;
	if (scene->res->h > y)
		scene->res->h = y;
	if (scene->res->w <= 0 || scene->res->h <= 0)
		error_and_quit(scene, "Resolution size must be superior to zero");
}
