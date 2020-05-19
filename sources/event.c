/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:03 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 16:43:42 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	listen_events(t_scene *scene)
{
	mlx_hook(scene->win->mlx_win, 17, 0, close_and_quit, scene);
	mlx_key_hook(scene->win->mlx_win, get_key, scene);
	mlx_mouse_hook(scene->win->mlx_win, get_mouse, scene);
	mlx_loop(scene->win->mlx_ptr);
}

int		close_and_quit(t_scene *scene)
{
	// destroy toutes les images
	mlx_clear_window(scene->win->mlx_ptr, scene->win->mlx_win);
	mlx_destroy_window(scene->win->mlx_ptr, scene->win->mlx_win);
	clear_scene(scene);
	exit(1);
	return (0);
}

int		get_key(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		close_and_quit(scene);
	if (key == KEY_E && ft_lstsize(scene->win->imgs) > 1)
		change_camera(scene, scene->win->img_id + 1);
	if (key == KEY_Q && ft_lstsize(scene->win->imgs) > 1)
		change_camera(scene, scene->win->img_id - 1);
	return (0);
}

/*
** button = 1 for normal click
** button = 2 for right click
*/

int		get_mouse(int button, int x, int y, t_scene *scene)
{
	(void)button;
	(void)x;
	(void)y;
	(void)scene;
	return (0);
}
