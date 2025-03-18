#include "../include/../include/cub3d.h"

/*void find_player_position(t_data *data)
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
}*/

void ft_resoures_initialisation(t_data *data)
{
    int i;

    i = -1;
    // Цикл проходит по всем четырем текстурам (например, стены в разных направлениях)
    while (++i < 4) 
    {
        // Загружаем XPM-изображение и привязываем его к `data->texture[i].img`
        data->texture[i].img = mlx_xpm_file_to_image(data->mlx, data->path_text[i],
                &data->texture[i].width, &data->texture[i].height);
        
        // Если изображение не удалось загрузить, выводим ошибку и завершаем программу
        if (!data->texture[i].img)
        {
            printf("Error\nCan't read texture file: %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }

        // Получаем доступ к пиксельным данным загруженного изображения
        data->texture[i].addr = mlx_get_data_addr(data->texture[i].img,
                &data->texture[i].bits_per_pixel, &data->texture[i].line_length,
                &data->texture[i].endian);
        
        // Если не удалось получить данные изображения, выводим ошибку и завершаем программу
        if (!data->texture[i].addr)
        {
            printf("Error\nFailed to get image data for texture:  %s\n", data->path_text[i]);
            ft_destroy_exit(data);
        }
    }

    /* 
    // Код для загрузки текстуры двери (раскомментируйте, если нужно добавить двери)
    
    // Загружаем текстуру двери из файла "textures/door.xpm"
    data->door_texture.img = mlx_xpm_file_to_image(data->mlx, "textures/door.xpm",
        &data->door_texture.width, &data->door_texture.height);

    // Если текстура двери не загружена, возвращаем FAILURE
    if (!data->door_texture.img)
        return (FAILURE);

    // Получаем доступ к пиксельным данным текстуры двери
    data->door_texture.addr = mlx_get_data_addr(data->door_texture.img,
        &data->door_texture.bpp, &data->door_texture.line_len, &data->door_texture.endian);
    */
}


void ft_param_initialisation(t_data *data)
{
    data->map_height = (int)(data->map_lines + 2);
    //data->map_height = 7;
    //data->map_width = 8;
    data->player_x = (float)data->y_pos;
    data->player_y = (float)data->x_pos;
    data->temp_j = 0;
    data->temp_i = 0;
    data->minimap = 0;
    //data->color_ceiling = 0x87CEEB;
   // data->color_floor = 0x2E8B57;
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


#include <stdio.h>
#include <stdlib.h>  // Для NULL

// Обработчик для движения мыши
int ft_mouse(int x, t_data *data) {
    if (data == NULL) {
        printf("Error: Invalid data (data is NULL).\n");
        return -1;
    }

    int mouse_delta_x = x - (WINDOW_W / 2);  // Центр экрана по оси X
    printf("Mouse X position: %d\n", x);
    printf("Mouse delta X: %d\n", mouse_delta_x);  // Отладочная информация

    // Если мышь перемещена, обновляем угол поворота
    if (mouse_delta_x != 0) {
        printf("11111\n");
        printf("player angle -= %f", data->player_angle);
        printf("Before update, player_angle: %f\n", data->player_angle);//122
        //data->player_angle += mouse_delta_x * STEP_ANGLE;  // STEP_ANGLE контролирует чувствительность
        if (data->player_angle >= 2 * M_PI) {
            data->player_angle -= 2 * M_PI;
        }
        if (data->player_angle < 0) {
            data->player_angle += 2 * M_PI;
        }
        printf("After update, player_angle: %f\n", data->player_angle);  // Отладочная информация
    }

    // Проверка перед вызовом mlx_mouse_move
    if (!data->mlx || !data->win) {
        printf("Error: mlx or win is NULL before mlx_mouse_move\n");
        return -1;
    }

    // Центрируем мышь
    printf("Resetting mouse position to center: (%d, %d)\n", WINDOW_W / 2, WINDOW_H / 2);
    mlx_mouse_move(data->mlx, data->win, WINDOW_W / 2, WINDOW_H / 2);

    return 0;
}

// Обработчик кликов мыши
int ft_mouse_click(int button, int x, int y, t_data *data) {
    printf("Mouse Clicked at X = %d, Y = %d, Button = %d\n", x, y, button);
    
    if (data != NULL) {
        data->player_x = x;
        data->player_y = y;
    }

    return 0;
}


// Главная инициализация
void part_2(t_data *data) {
    ft_param_initialisation(data);
    printf("After param init: mlx = %p, win = %p\n", data->mlx, data->win);
    ft_resoures_initialisation(data);
    printf("After resources init: mlx = %p, win = %p\n", data->mlx, data->win);

    // Проверка карты
    if (!data->map) {
        printf("Error: data->map is NULL\n");
        return;
    }

    printf("Player Position: X = %f, Y = %f, Angle = %f\n", data->player_x, data->player_y, data->player_angle);
    print_data(data);
    ft_draw(data);

    if (!data->mlx || !data->win) {
        printf("Error: mlx or window is not initialized.\n");
        return;
    }
    printf("player angle = %f", data->player_angle);

    // Добавление хуков
    //mlx_hook(data->win, MotionNotify, PointerMotionMask, ft_mouse, data); // Движение мыши
  //  mlx_mouse_hook(data->win, ft_mouse_click, data);  // Обработчик кликов мыши
    mlx_hook(data->win, KeyPress, KeyPressMask, ft_key, data); // Обработка клавиш
    mlx_hook(data->win, DestroyNotify, NoEventMask, ft_destroy_exit, data); // Закрытие окна

    //mlx_loop_hook(data->mlx, loop, data); // Обновление состояния каждую итерацию

    printf("Starting mlx_loop()\n");
    mlx_loop(data->mlx);
    printf("Exiting mlx_loop()\n");  // Эта строка никогда не должна выполняться
}
