#include "minirt.h"

/*
** parsing of the file with get next line
** read MLX (use image to show scene)
*/

int main(void)
{
	t_data		*window;
	t_camera	*camera;
	t_shape		*sphere;
	t_shape		*plane;
	t_list		*scene;
	// parse file + file errors
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