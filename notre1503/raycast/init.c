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
    //data->map_height = (int)(data->map_lines + 2);
    data->map_height = 7;
    data->map_width = 8;
    data->player_x = (float)data->x_pos;
    data->player_y = (float)data->y_pos;
    data->temp_j = 0;
    data->temp_i = 0;
    data->color_ceiling = 0x87CEEB;
    data->color_floor = 0x2E8B57;
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
#include <stdio.h>

void print_data(t_data *data) {
    printf("=== t_data Structure ===\n");


    printf("\nmap_height: %d\n", data->map_height);
    printf("map_width: %d\n", data->map_width);
    printf("x_pos: %d\n", data->x_pos);
    printf("y_pos: %d\n", data->y_pos);

    printf("\nplayer_x: %f\n", data->player_x);
    printf("player_y: %f\n", data->player_y);
    printf("player_angle: %f\n", data->player_angle);


    printf("\nNew Map:\n========================\n");
    for (int i = 0; i < data->map_height; i++) {
        for (int j = 0; j < data->map_width; j++) {
            printf("%c", data->new_map[i][j]);
        }
        printf("\n");
    }
}


void part_2(t_data *data) {
    ft_param_initialisation(data);
    printf("After param init: mlx = %p, win = %p\n", data->mlx, data->win);
    ft_resoures_initialisation(data);
    printf("After resources init: mlx = %p, win = %p\n", data->mlx, data->win);

    if (!data->map) {
        printf("Error: data->map is NULL\n");
        return;
    }

    // Убедимся, что игрок инициализирован
    printf("Player Position: X = %f, Y = %f, Angle = %f\n", data->player_x, data->player_y, data->player_angle);

    print_data(data);
    ft_draw(data);
    if (!data->mlx || !data->win) {
        printf("Ошибка: mlx или окно не инициализированы\n");
        return;
    }
    
    // Правильный порядок хуков перед mlx_loop()
    mlx_hook(data->win, 2, 1L << 0, ft_key, (void *)data); // Обработка клавиш
    mlx_hook(data->win, 17, 0, ft_destroy_exit, (void *)data); // Закрытие окна
    printf("Starting mlx_loop()\n");
    mlx_loop(data->mlx);
    printf("Exiting mlx_loop()\n");  // Эта строка никогда не должна выполняться
    

    // ❌ Удаляем ft_destroy_exit(data);, он здесь не нужен!
}

