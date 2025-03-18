#include "../include/../include/cub3d.h"

void ft_move(t_data *data, int direction)
{
    float dist;
    float move_x, move_y;
    float angle;

    // Учитываем направление движения
    angle = data->player_angle + direction * M_PI / 2;
    printf("[DEBUG] Before move: posX=%f, pos=%f\n", data->player_x, data->player_y);
    printf("[DEBUG] Player angle: %f, Direction: %d, Move angle: %f\n", data->player_angle, direction, angle);

    move_x = STEP_LINE * cos(angle);
    move_y = STEP_LINE * sin(angle);
    printf("00[DEBUG] Calculated move vector: move_x=%f, move_y=%f\n", move_x, move_y);

    // Проверка столкновения по Y
    dist = trace_ray(data, get_sign(move_y) * M_PI / 2);
    printf("11[DEBUG] Collision check Y: ray_angle=%f, dist=%f\n", get_sign(move_y) * M_PI / 2, dist);
    if (dist < fabs(move_y)) {
        printf("[DEBUG] Collision detected on Y axis. Stopping move_y.\n");
        move_y = 0;
    }

    // Проверка столкновения по X
    dist = trace_ray(data, (1 - (get_sign(move_x) + 1) / 2) * M_PI);
    printf("22[DEBUG] Collision check X: ray_angle=%f, dist=%f\n", (1 - (get_sign(move_x) + 1) / 2) * M_PI, dist);
    if (dist < fabs(move_x)) {
        printf("[DEBUG] Collision detected on X axis. Stopping move_x.\n");
        move_x = 0;
    }

    // Дополнительная проверка на диагональные столкновения
    /*dist = trace_ray(data, angle);
    if (dist < hypot(move_x, move_y)) {
        if (get_sign(move_x) * get_sign(move_y) != 0) {
            printf("[DEBUG] Diagonal collision detected. Stopping move_y and move_x.\n");
            move_y = 0;  // Останавливаем движение по оси Y
            move_x = 0;  // Останавливаем движение по оси X
        }
    }*/
    

    printf("[DEBUG] Before move: X=%f, Y=%f\n", data->player_x, data->player_y);

    // Обновляем позицию игрока
    data->player_x += move_x;
    data->player_y -= move_y; // Минус из-за системы координат

    printf("[DEBUG] After move: X=%f, Y=%f\n", data->player_x, data->player_y);
    printf("_____________________________________________________");
}


/*Определяет направление движения (направо/налево).
Вычисляет смещение move_x и move_y.
Проверяет столкновения (X, Y, диагональные).
Обновляет координаты игрока, если нет препятствий.*/


int ft_key(int keycode, t_data *data)
{
    printf("Key pressed: %d\n", keycode);
    if (keycode == 65307)
    {
        ft_destroy_exit(data);
        mlx_loop_end(data->mlx);
    }
    
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
    else if (keycode == 113)  // Q key
    {
        // Переключение миникарты
        data->minimap = (data->minimap == 0) ? 1 : 0;
    }
   /* else if (keycode == KEY_E)
        toggle_door(game);*/
    else
        return (0);
    ft_draw(data);
    return (0);
}

