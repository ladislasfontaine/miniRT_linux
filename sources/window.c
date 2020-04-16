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

void	color_window(t_data data, t_camera camera, t_shape sphere)
{
	int			i;
	int			j;
	float		u;
	float		v;
	t_ray		*ray;
	t_intersec	*intersec;

	j = 0;
	while (j < 480)
	{
		i = 0;
		while (i < 640)
		{
			u = (2.0f * i) / 640.0 - 1.0f;
			v = (-2.0f * j) / 480.0 + 1.0f;
			ray = make_ray(&camera, u, v);
			intersec = init_intersection(ray);
			sphere_intersection(intersec, &sphere);
			if (intersected(intersec))
				mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, j, 160230000);
			else
				mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, j, 50);
			i++;
		}
		j++;
	}
    mlx_loop(data.mlx_ptr);
}