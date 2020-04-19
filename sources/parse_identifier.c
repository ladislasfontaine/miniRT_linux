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
	if (scene->ambient->ratio != -1 || scene->ambient->color)
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
	// parse color next
	return (0);
}