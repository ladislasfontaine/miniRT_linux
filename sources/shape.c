#include "minirt.h"

t_shape		*init_shape(void)
{
	t_shape	*new;

	new = (t_shape *)malloc(sizeof(t_shape));
	if (!new)
		return (NULL);
	new->id = 1;
	new->diameter = 0.0;
	new->center = NULL;
	new->position = NULL;
	new->normal = NULL;
	new->color = NULL;
	return (new);
}
