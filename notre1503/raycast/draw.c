#include "../include/cub3d.h"

int ft_prepare_texture(t_data *data, float distance, t_draw_params *params)
{
    // Получаем указатель на текстуру, используя индекс textur_index
    params->texture = &data->texture[data->textur_index];

    // Проверяем, был ли корректно установлен указатель на текстуру
    if (!params->texture) {
        printf("Error: texture pointer is NULL! Index: %d\n", data->textur_index);
        return (0);  // Возвращаем 0 в случае ошибки
    }
    
    // Проверяем, была ли загружена текстура (есть ли доступ к пиксельным данным)
    if (!params->texture->addr) {  // Строка 6
        printf("Error: texture with index %d not loaded!\n", data->textur_index);
        return (0);  // Возвращаем 0 в случае ошибки
    }
    
    // Вычисляем высоту линии проекции (сколько пикселей будет занимать стена на экране)
    params->line_height = (float)WINDOW_H / distance;

    // Начальная позиция текстуры (сверху)
    params->texture_position = 0;

    // Шаг, с которым текстура будет наноситься на проекцию стены
    params->texture_step = (float)params->texture->height / params->line_height;

    // Если высота проекции больше высоты окна, корректируем текстуру
    if (params->line_height > WINDOW_H) {
        // Смещаем начальную позицию текстуры, чтобы она правильно отображалась
        params->texture_position = 0.5 * (params->line_height - WINDOW_H) / params->line_height * params->texture->height;
        params->line_height = WINDOW_H;  // Ограничиваем высоту линии окна
    }
    
    return (1);  // Возвращаем 1 при успешном выполнении
}

/*Получаем текстуру по индексу textur_index.
Проверяем, загрузилась ли текстура — если нет, выводим ошибку и возвращаем 0.
Вычисляем высоту проекции стены в зависимости от расстоянияdistance.
Определяем, как будет отображаться текстура на стене.
Если проекция выходит за границы экрана, корректируем*/

void ft_draw_column(t_data *data, int x, t_draw_params *params)
{
    unsigned int *texture_pixel_start; // Указатель на пиксели текстуры
    unsigned int *image_pixel_line;    // Указатель на пиксели изображения
    float texture_x;                   // Координата X в текстуре
    unsigned int i;                     // Счетчик пикселей

    i = 0;  // Обнуляем счетчик

    // Получаем указатель на начало данных текстуры
    texture_pixel_start = (unsigned int *)params->texture->addr;

    // Если сдвиг текстуры установлен, используем его, иначе 0
    if (data->textur_shift >= 0)
        texture_x = data->textur_shift;
    else
        texture_x = 0;

    // Смещаем указатель на нужную колонку текстуры
    texture_pixel_start += (int)(texture_x * params->texture->width);

    // Вычисляем начальную Y-координату для отрисовки на экране
    int start_y = (WINDOW_H - (int)params->line_height) / 2;
    if (start_y < 0) start_y = 0; // Если выходит за границы экрана, корректируем

    // Устанавливаем указатель на строку в буфере изображения
    image_pixel_line = (unsigned int *)data->img.addr + x + start_y * WINDOW_W;

    // Цикл отрисовки столбца пикселей
    while (i < (unsigned int)params->line_height)
    {
        // Копируем пиксель из текстуры в буфер изображения
        *image_pixel_line = *(texture_pixel_start + ((int)params->texture_position) * params->texture->width);

        // Смещаем указатель на следующую строку в буфере изображения
        image_pixel_line += WINDOW_W;

        // Продвигаем позицию в текстуре
        params->texture_position += params->texture_step;

        // Увеличиваем счетчик
        i++;
    }
}
/*Определяем указатели на данные текстуры и изображения.
Рассчитываем координаты текстуры для корректного отображениtextur_shift).
Определяем, с какого Y-значения начинать рисовать столбец (центрируем проекцию стены).
Проходим по всем пикселям столбца, копируя их из текстуры в изображение.
Изменяем координаты в текстуре, чтобы обеспечить правильное масштабирование.*/


void ft_draw_vertical_line(t_data *data, int x, float distance)
{
    t_draw_params params;
    if (distance <= 0.0001) {
        printf("Warning: distance too small or zero! Skipping column %d\n", x);
        return;
    }
    

    if (!ft_prepare_texture(data, distance, &params))
        return ;
    ft_draw_column(data, x, &params);
}

void ft_init_vertical_line(t_data *data)
{
    int x;                       // Координата X для отрисовки линии
    float angle_step;             // Шаг изменения угла между лучами
    float angle_premier;          // Текущий угол луча
    float distance;               // Расстояние до пересечения с объектом
    float correct_distance;       // Исправленное расстояние (с учетом искажений)

    // Начальный угол — это направление игрока + половина угла обзора
    angle_premier = data->player_angle + (VIEW_ANGLE / 2);

    // Вычисляем шаг угла между лучами
    angle_step = VIEW_ANGLE / (WINDOW_W - 1);
    
    x = 0;  // Начинаем трассировку с левого края экрана
    while (x < WINDOW_W)
    {
        // Запускаем трассировку луча под углом `angle_premier`
        distance = trace_ray(data, angle_premier);

        // Проверка на слишком маленькое расстояние (защита от ошибок)
        if (distance <= 0.0001) {
            printf("Warning: distance too small at x=%d, angle=%f\n", x, angle_premier);
            //continue;  // Если раскомментировать, этот луч будет пропущен
        }
        
        // Корректируем расстояние, убирая эффект "рыбьего глаза"
        correct_distance = distance * cos(data->player_angle - angle_premier);

        // Рисуем вертикальную линию (стену) на экране
        ft_draw_vertical_line(data, x, correct_distance);

        // Уменьшаем угол для следующего луча (двигаемся справа налево)
        angle_premier -= angle_step;

        // Переход к следующему столбцу экрана
        x++;
    }
}

/*Устанавливаем начальный угол angle_premier, который начинается с максимального угла обзора игрока.
Рассчитываем шаг углаangle_step так, чтобы лучи равномерно распределялись по ширине экрана.
В цикле трассируем лучи (trace_ray) и получаем расстояние до ближайшей стены.
Проверяем, не слишком ли маленькое расстояние, чтобы избежать ошибок при рендеринге.
Корректируем искажения перспективы, вызванные разницей в углах зрения.
Вызываем ft_draw_vertical_line(), которая рисует вертикальный столбец стены.
Переходим к следующему лучу, уменьшая угол.*/

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

#define TILE_SIZE 64  // Добавлено определение TILE_SIZE


// Функция для рисования пикселя на изображении
void put_pixel(t_image *img, int x, int y, int color) {
    char *dst;
    if (x < 0 || x >= WINDOW_W || y < 0 || y >= WINDOW_H)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

// Функция для рисования квадрата с заданным цветом
void draw_square(t_image *img, int x, int y, int color, int scale) {
    int i, j;
    if (x < 0 || y < 0 || x + scale > WINDOW_W || y + scale > WINDOW_H)
        return;
    for (i = 0; i < scale; i++) {
        for (j = 0; j < scale; j++) {
            put_pixel(img, x + i, y + j, color);
        }
    }
}

// Функция инициализации цветов и масштаба карты
void bonus_map_init_pictures(t_data *data) {
    data->npc_color = 0xFF0000;  // Красный цвет для игрока
    data->wall_color = 0x000000; // Чёрный цвет для стен
    data->map_scale = fmin(WINDOW_W / data->map_width, WINDOW_H / data->map_height /5);
}

// Функция для рисования миникарты
void draw_minimap(t_data *data) {
    int x, y;
    if (data->minimap == 0) return;

    if (!data->new_map || data->map_width <= 0 || data->map_height <= 0) {
        printf("Ошибка: карта не инициализирована или имеет неправильные размеры.\n");
        return;
    }

    bonus_map_init_pictures(data);

    for (y = 0; y < data->map_height; y++) {
        for (x = 0; x < data->map_width; x++) {
            if (!data->new_map || !data->new_map[y]) {
                printf("Ошибка: некорректная строка карты на y=%d\n", y);
                continue;
            }
            
            if (data->new_map[y][x] == '1') {
                draw_square(&data->img, x * data->map_scale, y * data->map_scale, data->wall_color, data->map_scale);
            }
        }
    }

    // Рисуем игрока (красный квадрат) на миникарте
    if (data->player_x >= 0 && data->player_y >= 0) {
        int px = (int)((data->player_x ) * data->map_scale);
        int py = (int)((data->player_y ) * data->map_scale);
        draw_square(&data->img, px, py, data->npc_color, data->map_scale/2);
    }
}

// Функция отладки для вывода информации о карте
void print_map_info(t_data *data) {
    printf("Размер карты: %d x %d\n", data->map_width, data->map_height);
    printf("Размер клеток: %d x %d\n", data->map_scale, data->map_scale);
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
    draw_minimap(data);
    //if(data->minimap == 1)
       // draw_minimap(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
    mlx_destroy_image(data->mlx, data->img.img);
    return (0);
}
