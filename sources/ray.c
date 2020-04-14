#include "minirt.h"

t_ray		*init_ray(t_vector *u, t_vector *v, float t)
{
	t_ray	*new;

	if (!(new = (t_ray *)malloc(sizeof(t_ray))))
		return (NULL);
	new->origin = u;
	new->direction = v;
	new->max_t = t;
	return (new);
}

t_vector	*point_on_ray(t_ray ray, float t)
{
	float		x;
	float		y;
	float		z;
	t_vector	*point;

	x = ray.origin->x + ray.direction->x * t;
	y = ray.origin->y + ray.direction->y * t;
	z = ray.origin->z + ray.direction->z * t;
	point = init_vector(x, y, z);
	return (point);
}
