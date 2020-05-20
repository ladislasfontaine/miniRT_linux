/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 17:06:00 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 10:53:14 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		save_image(t_scene *scene)
{
	create_bmp_image(scene, BMP_FILE_NAME);
	close_and_quit(scene);
	return (0);
}

void	bitmap_file_header(t_scene *scene, int padding_size, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	if (!(file_header = ft_calloc(BMP_FILE_HEADER_SIZE, sizeof(unsigned char))))
		error_and_quit(scene, "Malloc failed");
	file_size = BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE
		+ (4 * scene->res->w + padding_size) * scene->res->h;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE);
	write(fd, file_header, BMP_FILE_HEADER_SIZE);
	ft_strdel((char**)&file_header);
}

void	bitmap_info_header(t_scene *scene, int fd)
{
	unsigned char	*info_header;

	if (!(info_header = ft_calloc(BMP_INFO_HEADER_SIZE, sizeof(unsigned char))))
		error_and_quit(scene, "Malloc failed");
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(scene->res->w);
	info_header[5] = (unsigned char)(scene->res->w >> 8);
	info_header[6] = (unsigned char)(scene->res->w >> 16);
	info_header[7] = (unsigned char)(scene->res->w >> 24);
	info_header[8] = (unsigned char)(scene->res->h);
	info_header[9] = (unsigned char)(scene->res->h >> 8);
	info_header[10] = (unsigned char)(scene->res->h >> 16);
	info_header[11] = (unsigned char)(scene->res->h >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(32);
	write(fd, info_header, BMP_INFO_HEADER_SIZE);
	ft_strdel((char**)&info_header);
}

void	create_bmp_image(t_scene *scene, char *file_name)
{
	int				i;
	int				fd;
	int				padding_size;
	unsigned char	padding[3];

	i = scene->res->h;
	ft_bzero(padding, 3);
	if (!(fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		error_and_quit(scene, "Could not create bmp file");
	padding_size = (4 - (scene->res->w * 4) % 4) % 4;
	bitmap_file_header(scene, padding_size, fd);
	bitmap_info_header(scene, fd);
	while (i > 0)
	{
		write(fd, ((t_img *)(scene->imgs->content))->data + ((i - 1) * scene->res->w * 32 / 8),
				((t_img *)(scene->imgs->content))->size_line);
		write(fd, padding, padding_size);
		i--;
	}
	close(fd);
}
