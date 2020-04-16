#include "minirt.h"

/*
** parsing of the file with get next line
** read MLX (use image to show scene)
*/

int		main(int ac, char **av)
{
	t_data		*window;
	t_camera	*camera;
	t_shape		*sphere;
	t_shape		*plane;
	t_list		*scene;

	if (arguments_error(ac, av))
		return (1);
	parse_file(av[1]);
	// create cameras
	// create shapes
	scene = NULL;
	camera = init_camera(init_vector(-5.0, 1.0, 0.0), init_vector(5.0, 0.0, 0.0), 640.0 / 480.0, 70);
	sphere = init_sphere(init_shape());
	plane = init_plane(init_shape(), init_vector(0.0, 0.0, 0.0), init_vector(0.0, 1.0, 0.0));

	ft_lstadd_back(&scene, ft_lstnew((void *)sphere));
	ft_lstadd_back(&scene, ft_lstnew((void *)plane));
    if (!(window = init_window()))
		return (1);
    color_window(*window, *camera, scene);
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
