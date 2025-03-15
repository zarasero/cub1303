#include "../include/../include/cub3d.h"

void find_player_position(t_data *data)
{
    while (data->temp_i < data->map_height)
    {
        while (data->temp_j < data->map_width)
        {
            if (strchr("NSWE", data->new_map[data->temp_i][data->temp_j]))
            {
                data->player_x = data->temp_j;
                data->player_y = data->temp_i;
                if (data->new_map[data->temp_i][data->temp_j] == 'E')
                    data->player_angle = 0;
                else if (data->new_map[data->temp_i][data->temp_j] == 'N')
                    data->player_angle = M_PI / 2;
                else if (data->new_map[data->temp_i][data->temp_j] == 'W')
                    data->player_angle = M_PI;
                else if (data->new_map[data->temp_i][data->temp_j] == 'S')
                    data->player_angle = 3 * M_PI / 2;
                return;
            }
            data->temp_j++;
        }
        data->temp_i++;
        data->temp_j = 0;
    }
}

void ft_resoures_initialisation(t_data *data)
{
    int i;

    i = -1;
    while (++i < 4) 
    {
        data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->path_text[i],
                &data->texture[i].width, &data->texture[i].height);
        if (!data->texture[i].img)
        {
            printf("Error\nCan't read texture file: %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }
        data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
                &data->texture[i].bits_per_pixel, &data->texture[i].line_length,
                &data->texture[i].endian);
        if (!data->texture[i].addr)
        {
            printf("Error\nFailed to get image data for texture:  %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }
    }
}

void ft_param_initialisation(t_data *data)
{
    data->map_height = 10;
    data->map_width = 12;
    data->player_x = 0.0;
    data->player_y = 0.0;
    data->temp_j = 0;
    data->temp_i = 0;
    data->color_ceiling = 0x87CEEB;
    data->color_floor = 0x2E8B57;
    data->path_text[0] = "./textures/N.xpm";
    data->path_text[1] = "./textures/E.xpm";
    data->path_text[2] = "./textures/S.xpm";
    data->path_text[3] = "./textures/W.xpm";
    data->mlx = mlx_init();
    if (!data->mlx)
    {
         printf("Error: mlx_init() returned NULL\n");
         exit(1);
    }
    data->win = mlx_new_window(data->mlx, WINDOW_W, WINDOW_H, "data");
    if (!data->win)
    {
        printf("Error: data.win == NULL\n");
        exit(1);
    }
}
void print_data(t_data *data)
{
    printf("=== Информация о текстурах ===\n");
    printf("Север: %s\n", data->path_text[0] ? data->path_text[0] : "Не задано");
    printf("Юг: %s\n", data->path_text[2] ? data->path_text[2] : "Не задано");
    printf("Запад: %s\n", data->path_text[3] ? data->path_text[3] : "Не задано");
    printf("Восток: %s\n", data->path_text[1] ? data->path_text[1] : "Не задано");

}

int main() {
    t_data data;
    char *new_map[] = {
        "111111111111",
        "100000000101",
        "100000010001",
        "1000000000S1",
        "100000010001",
        "100000000001",
        "100000000001",
        "100000000001",
        "100000010001",
        "111111111111",
    };
    data.new_map = new_map;
    ft_param_initialisation(&data);
    ft_resoures_initialisation(&data);
    find_player_position(&data);
    print_data(&data);
    ft_draw(&data);
    mlx_key_hook(data.win, ft_key, (void *)&data);
   // mlx_hook(data.win, 2, 1, ft_key, (void *)&data);
    mlx_hook(data.win, 17, 0, ft_destroy_exit, (void *)&data); 
   // mlx_hook(data.win, 17, 0, mlx_loop_end, (void *)&data); 
    mlx_loop(data.mlx);
    ft_destroy_exit(&data);
    return (0);
}
