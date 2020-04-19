#include "minirt.h"

int		parse_resolution(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->resolution->w != 0 || scene->resolution->h != 0)
	{
		ft_putstr("Error\nResolution can only be declared once\n");
		return (-1);
	}
	i += is_space(line + i);
	i += parse_int(line + i, &scene->resolution->w);
	i += is_space(line + i);
	i += parse_int(line + i, &scene->resolution->h);
	i += is_space(line + i);
	if (scene->resolution->w == -1 || scene->resolution->h == -1 || line[i])
	{
		ft_putstr("Error\nProblem parsing the resolution line\n");
		return (-1);
	}
	return (0);
}

int		parse_ambient(char *line, t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->ambient->ratio != -1 || scene->ambient->color->r != -1)
	{
		ft_putstr("Error\nAmbient lightning can only be declared once\n");
		return (-1);
	}
	i += is_space(line + i);
	i += parse_float(line + i, &scene->ambient->ratio);
	if (scene->ambient->ratio < 0.0 || scene->ambient->ratio > 1.0)
	{
		ft_putstr("Error\nAmbient ratio should be between 0.0 and 1.0\n");
		return (-1);
	}
	i += is_space(line + i);
	i += parse_color(line + i, scene->ambient->color);
	i += is_space(line + i);
	if (line[i])
	{
		ft_putstr("Error\nProblem parsing the ambient lightning line\n");
		return (-1);
	}
	if (scene->ambient->color->r < 0 || scene->ambient->color->r >255 ||
		scene->ambient->color->g < 0 || scene->ambient->color->g >255 ||
		scene->ambient->color->b < 0 || scene->ambient->color->b >255)
	{
		ft_putstr("Error\nEach color value should be between 0 and 255\n");
		return (-1);
	}
	return (0);
}

int		parse_camera(char *line, t_scene *scene)
{
	t_camera	*camera;
	int			i;

	camera = init_camera_null();
	ft_lstadd_back(&scene->cameras, ft_lstnew((void *)camera));
	camera = (t_camera *)(ft_lstlast(scene->cameras)->content);
	i = 0;
	i += is_space(line + i);
	i += parse_vector(line + i, camera->origin);
	i += is_space(line + i);
	i += parse_vector(line + i, camera->direction);
	i += is_space(line + i);
	i += parse_float(line + i, &camera->fov);
	i += is_space(line + i);
	if (camera->fov < 0.0 || camera->fov > 180.0)
	{
		ft_putstr("Error\nField of view (FOV) should be between 0 and 180 degrees\n"); // put line number
		return (-1);
	}
	if (camera->direction->x < -1.0 || camera->direction->x > 1.0 ||
		camera->direction->y < -1.0 || camera->direction->y > 1.0 ||
		camera->direction->z < -1.0 || camera->direction->z > 1.0 ||
		length(camera->direction) < 0.99 || length(camera->direction) > 1.01)
	{
		ft_putstr("Error\nProblem with the orientation vector for camera\n"); // put line number
		return (-1);
	}
	if (line[i])
	{
		ft_putstr("Error\nProblem parsing the camera line\n"); // put line number
		return (-1);
	}
	return (0);
}
