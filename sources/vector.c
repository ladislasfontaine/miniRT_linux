#include "minirt.h"

t_vector	*init_vector(float x, float y, float z)
{
	t_vector	*new;

	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

float		square(float x)
{
	return (x * x);
}

float		length_square(t_vector *u)
{
	return (square(u->x) + square(u->y) + square(u->z));
}

float		length(t_vector *u)
{
	return (sqrt(length_square(u)));
}

float		normalize(t_vector *u)
{
	double	len;

	len = length(u);
	u->x = u->x / len;
	u->y = u->y / len;
	u->z = u->z / len;
	return (len);
}

float		dot_product(t_vector *u, t_vector *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

t_vector	*cross_product(t_vector *u, t_vector *v)
{
	return (init_vector(((u->y * v->z) - (u->z * v->y)),
		((u->z * v->x) - (u->x * v->z)),
		((u->x * v->y) - (u->y * v->x))));
}

t_vector	*vector_diff(t_vector *u, t_vector *v)
{
	return (init_vector(u->x - v->x, u->y - v->y, u->z - v->z));
}

int			check_normal_vector(t_vector *u)
{
	if (u->x < -1.0 || u->x > 1.0 || u->y < -1.0 || u->y > 1.0 ||
		u->z < -1.0 || u->z > 1.0 || length(u) < 0.99 || length(u) > 1.01)
	{
		ft_putstr("Error\nProblem with the normalized vector\n"); // put line number
		return (-1);
	}
	return (0);
}
