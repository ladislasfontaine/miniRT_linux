#include "minirt.h"

t_scene	*init_scene(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	if (!(scene->resolution = (t_resolution *)malloc(sizeof(t_resolution))))
		return (NULL);
	scene->resolution->w = 0;
	scene->resolution->h = 0;
	if (!(scene->ambient = (t_ambient *)malloc(sizeof(t_ambient))))
		return (NULL);
	scene->ambient->ratio = -1;
	scene->ambient->color = NULL;
	scene->lights = NULL;
	scene->cameras = NULL;
	scene->shapes = NULL;
	scene->window = NULL;
	return (scene);
}