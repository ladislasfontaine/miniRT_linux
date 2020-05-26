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

t_image	*init_image(t_scene *scene)
{
	t_image	*image;

	if (!(image = (t_image *)malloc(sizeof(t_image))))
		error_and_quit(scene, "Malloc failed");
	image->bpp = 32;
	image->endian = 1;
	image->size_line = 4 * scene->res->w;
	image->mlx_img = NULL;
	image->data = NULL;
	return (image);
}

int		color_image(t_scene *scene, t_camera *camera, t_image *img)
{
	int			i;
	int			j;
	int			k;

	if (!(img->data = mlx_get_data_addr(img->mlx_img, &img->bpp,
				&img->size_line, &img->endian)))
		error_and_quit(scene, "Malloc failed");
	k = 0;
	j = 0;
	while (j < scene->res->h)
	{
		i = 0;
		while (i < scene->res->w)
		{
			check_rays(scene, img->data, (t_vector){i, j, k}, camera);
			k += 4;
			i++;
		}
		j++;
	}
	return (0);
}

void	create_images(t_scene *sc)
{
	t_list			*cameras;
	t_list			*element;
	t_resolution	*r;
	t_image			*img;

	cameras = sc->cameras;
	r = sc->res;
	while (cameras)
	{
		img = NULL;
		if (!(img = init_image(sc)))
			error_and_quit(sc, "Cannot initialize the minilibX image");
		if (!(element = ft_lstnew((void *)img)))
			error_and_quit(sc, "Malloc failed");
		ft_lstadd_back(&sc->imgs, element);
		img = (t_image *)(ft_lstlast(sc->imgs)->content);
		if (!(img->mlx_img = mlx_new_image(sc->win->mlx_ptr, r->w, r->h)))
			error_and_quit(sc, "Malloc for new image failed");
		color_image(sc, (t_camera *)cameras->content, img);
		cameras = cameras->next;
	}
	if (!sc->save)
		mlx_put_image_to_window(sc->win->mlx_ptr, sc->win->mlx_win,
					((t_image *)(sc->imgs->content))->mlx_img, 0, 0);
}
