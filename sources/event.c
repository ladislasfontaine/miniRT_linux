/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:03 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 16:00:57 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	listen_events(t_scene *scene)
{
	mlx_hook(scene->win->mlx_win, 33, 0, close_and_quit, scene);
	mlx_key_hook(scene->win->mlx_win, get_key, scene);
	mlx_expose_hook(scene->win->mlx_win, get_expose, scene);
	mlx_loop(scene->win->mlx_ptr);
}

int		close_and_quit(t_scene *scene)
{
	if (!scene->save && scene->win && scene->win->mlx_win)
	{
		mlx_clear_window(scene->win->mlx_ptr, scene->win->mlx_win);
		mlx_destroy_window(scene->win->mlx_ptr, scene->win->mlx_win);
	}
	clear_scene(scene);
	exit(0);
	return (0);
}

void	error_and_quit(t_scene *scene, char *error)
{
	ft_printf("Error\n%s\n", error);
	if (scene && !scene->save && scene->win &&
		scene->win->mlx_win && scene->win->mlx_ptr)
	{
		mlx_clear_window(scene->win->mlx_ptr, scene->win->mlx_win);
		mlx_destroy_window(scene->win->mlx_ptr, scene->win->mlx_win);
	}
	clear_scene(scene);
	exit(1);
}

int		get_key(int key, t_scene *scene)
{
	if (key == 65307)
		close_and_quit(scene);
	if (key == 101 && ft_lstsize(scene->imgs) > 1)
		change_camera(scene, scene->win->img_id + 1);
	if (key == 97 && ft_lstsize(scene->imgs) > 1)
		change_camera(scene, scene->win->img_id - 1);
	return (0);
}

int		get_expose(t_scene *scene)
{
	change_camera(scene, scene->win->img_id);
	return (0);
}
