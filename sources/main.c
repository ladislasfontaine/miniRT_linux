#include "minirt.h"

int main(void)
{
	t_data		*window;
	t_camera	*camera;
	t_shape		*sphere;
	// parse file + file errors
	// create cameras
	// create shapes
	camera = init_camera(init_vector(-50.0, 0.0, 20.0), init_vector(0.0, 0.0, 1.0), 480, 640);
	sphere = init_sphere(init_shape());
    if (!(window = init_window()))
		return (1);
    color_window(*window, *camera, *sphere);
    return (0);
}