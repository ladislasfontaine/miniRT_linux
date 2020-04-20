#include "minirt.h"

t_shape		*init_shape(void)
{
	t_shape	*new;

	new = (t_shape *)malloc(sizeof(t_shape));
	if (!new)
		return (NULL);
	new->id = 1;
	new->diameter = 0.0;
	new->height = 0.0;
	new->side = 0.0;
	new->center = (t_vector *)malloc(sizeof(t_vector));
	new->position = (t_vector *)malloc(sizeof(t_vector));
	new->normal = (t_vector *)malloc(sizeof(t_vector));
	new->p1 = (t_vector *)malloc(sizeof(t_vector));
	new->p2 = (t_vector *)malloc(sizeof(t_vector));
	new->p3 = (t_vector *)malloc(sizeof(t_vector));
	new->color = (t_color *)malloc(sizeof(t_color));
	return (new);
}
