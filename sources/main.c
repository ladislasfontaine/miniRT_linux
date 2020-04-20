#include "minirt.h"

/*
** add ft_printf for errors handling with line numbers
** listen on the window for smooth exit / resizing etc
** --save option to create an image
** read MLX (use image to show scene)
** error number function
*/

int		main(int ac, char **av)
{
	t_scene		*scene;

	scene = init_scene();
	if (arguments_error(ac, av))
		return (1);
	if (parse_file(av[1], scene))
		return (1);
    if (!(scene->window = init_window()))
		return (1);
    color_window(scene);
    return (0);
}

int		arguments_error(int ac, char **av)
{
	if (ac < 2 || ac > 3)
	{
		ft_putstr("Error\nWrong number of arguments (should be 1 or 2)\n");
		return (1);
	}
	if (ac == 3 && ft_strcmp(av[2], "--save") != 0)
	{
		ft_putstr("Error\nUnknown option (should be '--save')\n");
		return (1);
	}
	if (ft_strcmp((av[1] + ft_strlen(av[1]) - 3), ".rt") != 0)
	{
		ft_putstr("Error\nWrong file extension (should be '.rt')\n");
		return (1);
	}
	return (0);
}
