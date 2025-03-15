#include "../include/../include/cub3d.h"

void ft_move(t_data *data, int direction)
{
    float dist;
    float move_x, move_y;
    float angle;

    angle = data->player_angle + direction * M_PI / 2;
    move_x = STEP_LINE * cos(angle);
    move_y = STEP_LINE * sin(angle);
    dist = trace_ray(data, angle);
    if (dist < STEP_LINE)
        move_x = move_y = 0;
    data->player_x += move_x;
    data->player_y -= move_y;
}

int ft_key(int keycode, t_data *data)
{
    if (keycode == 65307)
       mlx_loop_end(data->mlx);
    else if (keycode == 65362 || keycode == 119)
        ft_move(data, 0);
    else if (keycode == 65364 || keycode == 115)
        ft_move(data, 2);
    else if (keycode == 97)
        ft_move(data, 1);
    else if (keycode == 100)
        ft_move(data, -1);
    else if (keycode == 65361 || keycode == 65363)
    {
        if (keycode == 65361)
          data->player_angle += STEP_ANGLE;
        else
            data->player_angle -= STEP_ANGLE;
        if (data->player_angle >= 2 * M_PI)
            data->player_angle -= 2 * M_PI;
        if (data->player_angle < 0)
            data->player_angle += 2 * M_PI;
        }
    else
        return (0);
    ft_draw(data);
    return (0);
}

