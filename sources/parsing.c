/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:59 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/12 09:03:41 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_file(char *file, t_scene *scene)
{
	int		fd;
	int		res;
	int		n;
	char	*line;

	res = 1;
	n = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("Error\nCannot open the file\n");
		return (1);
	}
	while (res)
	{
		res = get_next_line(fd, &line);
		if (res == -1)
		{
			ft_printf("Error\nCannot read the file\n");
			return (1);
		}
		if (parse_line(line, scene, n) == -1)
			return (1);
		free(line);
		n++;
	}
	if (close(fd) == -1)
	{
		ft_printf("Error\nCannot close the file\n");
		return (1);
	}
	return (0);
}

int		parse_line(char *line, t_scene *scene, int n)
{
	int		i;
	int		ret;

	i = 0;
	i += is_space(line + i);
	if (!line[i])
		return (0);
	if (ft_strncmp(line + i, "R ", 2) == 0)
		ret = parse_resolution(line + i + 2, scene, n);
	else if (ft_strncmp(line + i, "A ", 2) == 0)
		ret = parse_ambient(line + i + 2, scene, n);
	else if (ft_strncmp(line + i, "c ", 2) == 0)
		ret = parse_camera(line + i + 2, scene, n);
	else if (ft_strncmp(line + i, "l ", 2) == 0)
		ret = parse_light(line + i + 2, scene, n);
	else if (ft_strncmp(line + i, "sp ", 3) == 0)
		ret = parse_sphere(line + i + 3, scene, n);
	else if (ft_strncmp(line + i, "pl ", 3) == 0)
		ret = parse_plane(line + i + 3, scene, n);
	else if (ft_strncmp(line + i, "sq ", 3) == 0)
		ret = parse_square(line + i + 3, scene, n);
	else if (ft_strncmp(line + i, "cy ", 3) == 0)
		ret = parse_cylinder(line + i + 3, scene, n);
	else if (ft_strncmp(line + i, "tr ", 3) == 0)
		ret = parse_triangle(line + i + 3, scene, n);
	else
	{
		ft_printf("Error\nLine %d. Unknown identifier in the .rt file\n", n);
		return (-1);
	}
	return (ret);
}
