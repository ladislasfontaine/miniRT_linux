/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lafontai <lafontai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:19:59 by lafontai          #+#    #+#             */
/*   Updated: 2020/05/20 15:19:23 by lafontai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parse_file(char *file, t_scene *scene)
{
	int		fd;
	int		res;

	res = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		error_and_quit(scene, "Cannot open the file");
	while (res)
	{
		res = get_next_line(fd, &scene->line);
		if (res == -1)
			error_and_quit(scene, "Cannot read the file");
		parse_line(scene->line, scene);
		free(scene->line);
		scene->line = NULL;
	}
	if (close(fd) == -1)
		error_and_quit(scene, "Cannot close the file");
	return (0);
}

void	parse_line(char *line, t_scene *scene)
{
	int		i;

	i = is_space(line);
	if (!line[i])
		return ;
	if (ft_strncmp(line + i, "R ", 2) == 0)
		parse_resolution(line + i + 2, scene);
	else if (ft_strncmp(line + i, "A ", 2) == 0)
		parse_ambient(line + i + 2, scene);
	else if (ft_strncmp(line + i, "c ", 2) == 0)
		parse_camera(line + i + 2, scene);
	else if (ft_strncmp(line + i, "l ", 2) == 0)
		parse_light(line + i + 2, scene);
	else if (ft_strncmp(line + i, "sp ", 3) == 0)
		parse_sphere(line + i + 3, scene);
	else if (ft_strncmp(line + i, "pl ", 3) == 0)
		parse_plane(line + i + 3, scene);
	else if (ft_strncmp(line + i, "sq ", 3) == 0)
		parse_square(line + i + 3, scene);
	else if (ft_strncmp(line + i, "cy ", 3) == 0)
		parse_cylinder(line + i + 3, scene);
	else if (ft_strncmp(line + i, "tr ", 3) == 0)
		parse_triangle(line + i + 3, scene);
	else
		error_and_quit(scene, "Unknown identifier in the .rt file");
}

int		is_space(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		parse_int(t_scene *scene, char *line, int *n)
{
	if (ft_isdigit(line[0]) || line[0] == '-')
	{
		*n = ft_atoi(line);
		return (ft_numlen(*n));
	}
	error_and_quit(scene, "Error in integer format");
	return (0);
}
