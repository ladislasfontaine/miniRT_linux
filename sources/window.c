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
	int	i;
	int	j;

	ft_putnbr((int)camera.w);
	ft_putnbr((int)sphere.diameter);
	j = 100;
	while (j < 380)
	{
		i = 100;
		while (i < 540)
		{
			mlx_pixel_put(data.mlx_ptr, data.mlx_win, i, j, 160230000);
			i++;
		}
		j++;
	}
    mlx_loop(data.mlx_ptr);
}