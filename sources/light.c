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

	light = (t_light *)lights->content;
	point = get_point(intersec->ray->origin, intersec->ray->direction, intersec->t);
	light_dir = vector_diff(light->origin, point);
	normalize(light_dir);
	light_ratio = dot_product(light_dir, intersec->normal);
	set_shadow(intersec->color, light_ratio);

	// créer un intersec avec un ray qui part du point vers light
	// puis méthode check_all_shapes pour voir si intersection
}

void	set_shadow(t_color *color, float ratio)
{
	if (!color)
		return ;
	if (ratio <= 0.0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else
	{
		color->r *= ratio;
		color->g *= ratio;
		color->b *= ratio;
	}
	if (color->r > 255)
		color->r = 255;
	if (color->g > 255)
		color->g = 255;
	if (color->b > 255)
		color->b = 255;
}
