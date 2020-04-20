#include "minirt.h"

/*
** parsing of the file with get next line
** add ft_printf for errors handling with line numbers
** camera remove aspect ratio from init function
** listen on the window for smooth exit / resizing etc
** --save option to create an image
** read MLX (use image to show scene)
** error number function
*/

int		main(int ac, char **av)
{
	t_scene		*scene;

	t_camera	*camera;
	t_shape		*sphere;
	t_shape		*plane;
	t_shape		*shape;

	scene = init_scene();
	
	camera = init_camera(init_vector(-5.0, 1.0, 0.0), init_vector(5.0, 0.0, 0.0), 640.0 / 480.0, 70);
	ft_lstadd_back(&scene->cameras, ft_lstnew((void *)camera));
	plane = init_plane(init_shape(), init_vector(0.0, 0.0, 0.0), init_vector(0.0, 1.0, 0.0));
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)plane));
	sphere = init_sphere(init_shape());
	ft_lstadd_back(&scene->shapes, ft_lstnew((void *)sphere));

	if (arguments_error(ac, av))
		return (1);
	if (parse_file(av[1], scene))
	{
		shape = (t_shape *)(ft_lstlast(scene->shapes)->content);
		/*
		printf("Shape id: %d\nColor: %d, %d, %d\nVector center: %f, %f, %f\nVector position: %f, %f, %f\nVector normal: %f, %f, %f\nVector p1: %f, %f, %f\nVector p2: %f, %f, %f\nVector p3: %f, %f, %f\nDiameter: %f\nHeight: %f\nSide: %f\n",
		shape->id, shape->color->r, shape->color->g, shape->color->b, shape->center->x, shape->center->y, shape->center->z,
		shape->position->x, shape->position->y, shape->position->z,
		shape->normal->x, shape->normal->y, shape->normal->z, shape->p1->x, shape->p1->y, shape->p1->z,
		shape->p2->x, shape->p2->y, shape->p2->z, shape->p3->x, shape->p3->y, shape->p3->z, shape->diameter, shape->height, shape->side);
		*/
		return (1);
	}
	
	
	// create shapes

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
