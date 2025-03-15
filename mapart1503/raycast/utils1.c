
#include "../include/cub3d.h"

int get_sign(float value)
{
    if (value < 0)
        return (-1);
    return (1);
}

int ft_destroy_exit(t_data *data)
{
    int i;

    mlx_clear_window(data->mlx, data->win);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    i = -1;
    while (++i < 4)
    {
        if (data->texture[i].img)
            mlx_destroy_image(data->mlx, data->texture[i].img);
    }
    if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
    exit(0);
}
