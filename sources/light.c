#include "minirt.h"

t_light	*init_light_null(void)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = (t_vector *)malloc(sizeof(t_vector));
	light->color = (t_color *)malloc(sizeof(t_color));
	light->brightness = 0;
	return (light);
}

void	check_all_lights(t_list *lights, t_intersec *intersec)
{
	t_light		*light;
	t_vector	*light_dir;
	t_vector	*point;
	float		light_ratio;
	float		x;
	float		y;
	float		z;

	light = (t_light *)lights->content;
	x = intersec->ray->origin->x + intersec->t * intersec->ray->direction->x;
	y = intersec->ray->origin->y + intersec->t * intersec->ray->direction->y;
	z = intersec->ray->origin->z + intersec->t * intersec->ray->direction->z;
	point = init_vector(x, y, z);
	light_dir = vector_diff(light->origin, point);
	normalize(light_dir);
	light_ratio = dot_product(light_dir, intersec->normal);
	if (light_ratio > 0.0)
	{
		intersec->color->r *= light_ratio;
		intersec->color->g *= light_ratio;
		intersec->color->b *= light_ratio;
	}
	else
	{
		intersec->color->r = 0;
		intersec->color->g = 0;
		intersec->color->b = 0;
	}
	//if (intersec->shape->id == SPHERE)
	//	printf("Light ratio: %f\n", light_ratio);
	// quantité de lumière = dot product (direction source lumineuse, normale du point d'intersection)
}
