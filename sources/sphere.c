#include "minirt.h"

t_shape	*init_sphere(t_shape *sphere)
{
	sphere->diameter = 12.6;
	sphere->center = init_vector(0.0, 0.0, 20.6);
	sphere->color_r = 160;
	sphere->color_g = 230;
	sphere->color_b = 0;
	return (sphere);
}

int		sphere_intersection(t_intersec *intersec, t_shape *sphere)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	t_ray	*local_ray;

	local_ray = init_ray(vector_diff(intersec->ray->origin, sphere->center), intersec->ray->direction, intersec->ray->max_t);
	if (!local_ray)
		return (0);
	a = length_square(local_ray->direction);
	b = 2 * dot_product(local_ray->direction, local_ray->origin);
	c = length_square(local_ray->origin) - square(sphere->diameter / 2.0);
	free(local_ray->origin);
	free(local_ray);
	discriminant = square(b) - 4 * a * c;
	if (discriminant < 0.0f)
		return (0);
	if (sphere_points(intersec, a, b, discriminant))
	{
		intersec->shape = sphere;
		return (1);
	}
	return (0);
}

int		sphere_points(t_intersec *intersec, float a, float b, float discriminant)
{
	float	t1;
	float	t2;

	t1 = (-b - sqrtf(discriminant)) / (2 * a);
	t2 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t1 > RAY_MIN && t1 < intersec->t)
		intersec->t = t1;
	else if (t2 > RAY_MIN && t2 < intersec->t)
		intersec->t = t2;
	else
		return (0);
	return (1);
}
