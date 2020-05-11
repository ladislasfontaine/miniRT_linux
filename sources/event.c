/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:03 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/11 16:06:55 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	listen_events(t_scene *scene)
{
	mlx_hook(scene->window->mlx_win, 17, 0, close_and_quit, scene);
	mlx_key_hook(scene->window->mlx_win, get_key, scene);
	mlx_mouse_hook(scene->window->mlx_win, get_mouse, scene);
	mlx_loop(scene->window->mlx_ptr);
}

int		close_and_quit(t_scene *scene)
{
	mlx_clear_window(scene->window->mlx_ptr, scene->window->mlx_win);
	mlx_destroy_window(scene->window->mlx_ptr, scene->window->mlx_win);
	exit(1);
	return (0);
}

int		get_key(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		close_and_quit(scene);
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
