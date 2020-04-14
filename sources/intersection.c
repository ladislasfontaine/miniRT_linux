#include "minirt.h"

int			intersected(t_intersec *intersec)
{
	if (!intersec->shape)
		return (0);
	return (1);
}

t_vector	*intersection(t_intersec *intersec)
{
	return (point_on_ray(*(intersec->ray), intersec->t));
}
