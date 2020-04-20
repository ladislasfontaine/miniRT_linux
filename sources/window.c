#include "minirt.h"

t_data	*init_window(void)
{
    t_data  *data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
    if (!(data->mlx_ptr = mlx_init()))
	{
		ft_putstr("Error\nCannot initialize the minilibX\n");
        return (NULL);
	}
    if ((data->mlx_win = mlx_new_window(data->mlx_ptr, 640, 480, "miniRT project")) == NULL)
    {
		ft_putstr("Error\nCannot create a new window\n");
        return (NULL);
	}
    return (data);
}

void	color_window(t_scene *scene)
{
	int			i;
	int			j;
	float		u;
	float		v;
	t_intersec	*intersec;

	j = 0;
	while (j < scene->resolution->h)
	{
		i = 0;
		while (i < scene->resolution->w)
		{
			u = (2.0f * i) / (float)scene->resolution->w - 1.0f;
			v = (-2.0f * j) / (float)scene->resolution->h + 1.0f;
			intersec = init_intersection(make_ray(scene, (t_camera *)scene->cameras->content, u, v));
			check_all_shapes(scene->shapes, intersec);

			if (intersected(intersec) && intersec->shape->id == SPHERE)
				mlx_pixel_put(scene->window->mlx_ptr, scene->window->mlx_win, i, j, rgb_to_int(200, 20, 255));
			else if (intersected(intersec) && intersec->shape->id == PLANE)
				mlx_pixel_put(scene->window->mlx_ptr, scene->window->mlx_win, i, j, 255);
			else
				mlx_pixel_put(scene->window->mlx_ptr, scene->window->mlx_win, i, j, 50);
			i++;
		}
		j++;
	}
    mlx_loop(scene->window->mlx_ptr);
}

void	check_all_shapes(t_list *shapes, t_intersec *intersec)
{
	int		shape;
	t_list	*lst_cpy;

	lst_cpy = shapes;
	while (lst_cpy)
	{
		shape = ((t_shape *)(lst_cpy->content))->id;
		if (shape == PLANE)
			plane_intersection(intersec, (t_shape *)(lst_cpy->content));
		else if (shape == SPHERE)
			sphere_intersection(intersec, (t_shape *)(lst_cpy->content));
		lst_cpy = lst_cpy->next;
	}
}
