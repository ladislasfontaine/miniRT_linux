#include "minirt.h"

t_shape	*init_plane(t_shape *plane)
{
	plane->position = init_vector(0.0, 0.0, 0.0);
	plane->normal = init_vector(0.0, 1.0, 0.0);
	return (plane);
}

int		plane_intersection(t_intersec *intersec, t_shape *plane)
{
	float d_dot_n;
	float t;

	d_dot_n = dot_product(intersec->ray->direction, plane->normal);
	if (d_dot_n == 0.0f)
		return (0);
	t = dot_product(vector_diff(plane->position, intersec->ray->origin), plane->normal) / d_dot_n;
	if (t <= RAY_MIN || t >= intersec->t)
		return (0);
	intersec->t = t;
	intersec->shape = plane;
	return (1);
}
