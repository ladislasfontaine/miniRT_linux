#include "minirt.h"

t_intersec	*init_intersection(t_ray *ray)
{
	t_intersec	*new;

	if (!(new = (t_intersec *)malloc(sizeof(t_intersec))))
		return (NULL);
	new->ray = ray;
	new->shape = NULL;
	new->t = ray->max_t;
	new->color = init_color(0, 0, 0);
	return (new);
}

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
