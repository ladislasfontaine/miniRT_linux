#include "minirt.h"

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int main(void)
{
    data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (1);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 640, 480, "miniRT project")) == NULL)
        return (1);
    mlx_loop(data.mlx_ptr);
    return (0);
}