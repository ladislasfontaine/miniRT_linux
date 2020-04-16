#include "minirt.h"

/*
** chained list of shapes to get all the shapes on the scene
** parsing of the file with get next line
** read MLX (use image to show scene)
*/

int main(void)
{
	t_data		*window;
	t_camera	*camera;
	t_shape		*sphere;
	t_shape		*plane;
	// parse file + file errors
	// create cameras
	// create shapes
	camera = init_camera(init_vector(-5.0, 1.0, 0.0), init_vector(5.0, 0.0, 0.0), 640.0 / 480.0, 70);
	sphere = init_sphere(init_shape());
	plane = init_plane(init_shape());
    if (!(window = init_window()))
		return (1);
    color_window(*window, *camera, *sphere, *plane);
    return (0);
}