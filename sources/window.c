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

void	color_window(t_data data, t_camera camera, t_list *scene)
{
	int			i;
	int			j;
	float		u;
	float		v;
	t_intersec	*intersec;

	j = 0;
	while (j < 480)
	{
		i = 0;
		while (i < 640)
		{
			u = (2.0f * i) / 640.0 - 1.0f;
			v = (-2.0f * j) / 480.0 + 1.0f;
			intersec = init_intersection(make_ray(&camera, u, v));
			check_all_shapes(scene, intersec);

			if (intersected(intersec) && intersec->shape->id == SPHERE)
				mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, j, rgb_to_int(200, 20, 255));
			else if (intersected(intersec) && intersec->shape->id == PLANE)
				mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, j, 255);
			else
				mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, j, 50);
			i++;
		}
		j++;
	}
    mlx_loop(data.mlx_ptr);
}

void	check_all_shapes(t_list *scene, t_intersec *intersec)
{
	int		shape;
	t_list	*scene_cpy;

	scene_cpy = scene;
	while (scene_cpy)
	{
		shape = ((t_shape *)(scene_cpy->content))->id;
		if (shape == PLANE)
			plane_intersection(intersec, (t_shape *)(scene_cpy->content));
		else if (shape == SPHERE)
			sphere_intersection(intersec, (t_shape *)(scene_cpy->content));
		scene_cpy = scene_cpy->next;
	}
}
