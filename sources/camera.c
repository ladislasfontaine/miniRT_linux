#include "minirt.h"

t_camera	*init_camera(t_vector *origin, t_vector *orientation, float aspect_ratio, float fov)
{
	t_vector	*upguide;
	t_camera	*new;

	new = (t_camera *)malloc(sizeof(t_camera));
	if (!new)
		return (NULL);
	if (!(upguide = init_vector(0.0, 1.0, 0.0)))
		return (NULL);
	new->origin = origin;
	new->direction = orientation;
	normalize(new->direction);
	new->h = tan(fov / 180.0);
	new->w = new->h * aspect_ratio;
	new->fov = fov;
	new->right = cross_product(new->direction, upguide);
	normalize(new->right);
	new->up = cross_product(new->right, new->direction);
	free(upguide);
	return (new);
}

t_ray		*make_ray(t_camera *camera, float u, float v)
{
	t_vector	*origin;
	t_vector	*direction;
	float		x;
	float		y;
	float		z;

	origin = init_vector(camera->origin->x, camera->origin->y, camera->origin->z);
	if (!origin)
		return (NULL);
	x = camera->direction->x + u * camera->w * camera->right->x + v * camera->h * camera->up->x;
	y = camera->direction->y + u * camera->w * camera->right->y + v * camera->h * camera->up->y;
	z = camera->direction->z + u * camera->w * camera->right->z + v * camera->h * camera->up->z;
	direction = init_vector(x, y, z);
	if (!direction)
	{
		free(origin);
		return (NULL);
	}
	normalize(direction);
	return (init_ray(origin, direction, RAY_MAX));
}
