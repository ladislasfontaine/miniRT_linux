/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 11:49:24 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/19 14:48:06 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_img	*init_image(t_scene *scene)
{
	t_img	*image;

	if (!(image = (t_img *)malloc(sizeof(t_img))))
		return(NULL);
	image->bpp = 32;
	image->endian = 1;
	image->size_line = 4 * scene->res->w;
	image->mlx_img = NULL;
	return (image);
}
