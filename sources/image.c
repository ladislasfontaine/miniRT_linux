/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:49:24 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 16:11:22 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_img	*init_image(t_scene *scene)
{
	t_img	*image;

	if (!(image = (t_img *)malloc(sizeof(t_img))))
		error_and_quit(scene, "Malloc failed");
	image->bpp = 32;
	image->endian = 1;
	image->size_line = 4 * scene->res->w;
	image->mlx_img = NULL;
	image->data = NULL;
	return (image);
}
