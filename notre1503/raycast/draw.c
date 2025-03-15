#include "../include/cub3d.h"

int ft_prepare_texture(t_data *data, float distance, t_draw_params *params)
{
    params->texture = &data->texture[data->textur_index];
    if (!params->texture->addr)
    {
        printf("Error: texture with index %d not loaded!\n", data->textur_index);
        return (0);
    }
    params->line_height = (float)WINDOW_H / distance;
    params->texture_position = 0;
    params->texture_step = (float)params->texture->height / params->line_height;

    if (params->line_height > WINDOW_H) {
        params->texture_position = 0.5 * (params->line_height - WINDOW_H) / params->line_height * params->texture->height;
        params->line_height = WINDOW_H;
    }
    return (1);
}

void ft_draw_column(t_data *data, int x, t_draw_params *params)
{
    unsigned int *texture_pixel_start;
    unsigned int *image_pixel_line;
    float texture_x;
    unsigned int i;

    i = 0;
    texture_pixel_start = (unsigned int *)params->texture->addr;
    if (data->textur_shift >= 0)
        texture_x = data->textur_shift;
    else
        texture_x = 0;
    texture_pixel_start += (int)(texture_x * params->texture->width);
    image_pixel_line = (unsigned int *)data->img.addr + x + (WINDOW_H - (int)params->line_height) / 2 * WINDOW_W;
    while (i < (unsigned int)params->line_height)
    {
        *image_pixel_line = *(texture_pixel_start + ((int)params->texture_position) * params->texture->width);
        image_pixel_line += WINDOW_W;
        params->texture_position += params->texture_step;
        i++;
    }
}

void ft_draw_vertical_line(t_data *data, int x, float distance)
{
    t_draw_params params;

    if (!ft_prepare_texture(data, distance, &params))
        return ;
    ft_draw_column(data, x, &params);
}

void ft_init_vertical_line(t_data *data)
{
    int x;
    float angle_step;
    float angle_premier;  
    float distance;
    float correct_distance;

    angle_premier = data->player_angle + (VIEW_ANGLE / 2);
    angle_step = VIEW_ANGLE / (WINDOW_W - 1);
    x = 0;
    while (x < WINDOW_W)
    {
        distance = trace_ray(data, angle_premier);
        correct_distance = distance * cos(data->player_angle - angle_premier);
        ft_draw_vertical_line(data, x, correct_distance);
        angle_premier -= angle_step;
        x++;
    }
}

void ft_draw_ceiling_and_floor(t_data *data)
{
    unsigned int *dst;
    unsigned int i;
    unsigned int mid_height;

    mid_height = WINDOW_W * (WINDOW_H / 2);
    dst = (unsigned int *) data->img.addr;
    i = mid_height;
    while (i > 0)
    {
        *dst++ = data->color_ceiling;
        i--;
    }
    i = WINDOW_W * WINDOW_H - mid_height;
    while (i > 0)
    {
        *dst++ = data->color_floor;
        i--;
    }
}

int ft_draw(t_data *data)
{
    data->img.img = mlx_new_image(data->mlx, WINDOW_W, WINDOW_H);
    if (!data->img.img)
    {
        printf("Error: Failed to create a new image!");
        return (0);
    }
    data->img.addr = mlx_get_data_addr(data->img.img,
                                       &data->img.bits_per_pixel,
                                       &data->img.line_length,
                                       &data->img.endian);
    if (!data->img.addr)
    {
        printf("Error: Failed to get image data address!");
        mlx_destroy_image(data->mlx, data->img.img);
        return (0);
    }
    ft_draw_ceiling_and_floor(data);
    ft_init_vertical_line(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.img);
    return (0);
}
