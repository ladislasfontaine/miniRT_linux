#include "minirt.h"

t_shape	*init_sphere(t_shape *sphere)
{
	sphere->id = 2;
	sphere->diameter = 1.0;
	sphere->center = init_vector(0.0, 1.0, 0.0);
	sphere->color = NULL;
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
	discriminant = square(b) - (4 * a * c);
	if (discriminant < 0.0f)
		return (0);
	if (sphere_points(intersec, a, b, discriminant))
	{
		intersec->shape = sphere;
		intersec->color = init_color(intersec->shape->color->r, intersec->shape->color->g, intersec->shape->color->b);
		sphere_normal_vector(intersec);
		return (1);
	}
	return (0);
}

int		sphere_points(t_intersec *intersec, float a, float b, float discriminant)
{
	float	t1;
	float	t2;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > RAY_MIN && t1 < intersec->t)
		intersec->t = t1;
	else if (t2 > RAY_MIN && t2 < intersec->t)
		intersec->t = t2;
	else
		return (0);
	return (1);
}

int		sphere_normal_vector(t_intersec *intersec)
{
	float		x;
	float		y;
	float		z;
	t_vector	*point;

	x = intersec->ray->origin->x + intersec->t * intersec->ray->direction->x;
	y = intersec->ray->origin->y + intersec->t * intersec->ray->direction->y;
	z = intersec->ray->origin->z + intersec->t * intersec->ray->direction->z;
	point = init_vector(x, y, z);
	intersec->normal = vector_diff(point, intersec->shape->center);
	normalize(intersec->normal);
	free(point);
	return (0);
}
