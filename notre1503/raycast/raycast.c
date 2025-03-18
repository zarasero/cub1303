#include "../include/cub3d.h"

void initialize_ray(t_data *data, Ray *ray, float angle)
{
    ray->direction_x = cos(angle);  // Направление луча по оси X, вычисляемое через косинус угла
    ray->direction_y = -sin(angle); // Направление луча по оси Y, вычисляемое через синус угла (отрицательное, так как ось Y направлена вниз)
    ray->step_x = get_sign(ray->direction_x); // Определяем знак для шага по оси X (если направление положительное, шаг будет 1, иначе -1)
    ray->step_y = get_sign(ray->direction_y); // Определяем знак для шага по оси Y (если направление положительное, шаг будет 1, иначе -1)
    ray->next_vertical_x = (int)data->player_x; // Вычисляем следующее возможное пересечение вертикальной линии (X)
    if (ray->step_x > 0)
        ray->next_vertical_x +=1.0f;
    ray->next_horizontal_y = (int)data->player_y;
    if(ray->step_y > 0)
        ray->next_horizontal_y += 1.0f; // Вычисляем следующее возможное пересечение горизонтальной линии (Y)
   // ray->map_x = (int)ray->next_vertical_x; // Преобразуем координату X для карты в целое число
   // ray->map_y = (int)ray->next_vertical_y; // Преобразуем координату Y для карты в целое число
}

static float save_texture_info(t_data *data, float distance, int texture_index, float texture_x)
{
    data->textur_index = texture_index; // Сохраняем индекс текстуры
    data->textur_shift = texture_x; // Сохраняем смещение текстуры
    printf("DISTANCE = %f\n", distance);
    return (distance); // Возвращаем расстояние до пересечения
}

void calculate_next_intersection(t_data *data, Ray *ray)
{
    if (ray->step_x != 0) // Если шаг по X не равен нулю
    {
        ray->next_vertical_y = data->player_y + ray->direction_y / ray->direction_x * (ray->next_vertical_x - data->player_x); // Вычисляем пересечение вертикальной линии
        ray->vertical_distance = sqrt(pow(data->player_x - ray->next_vertical_x, 2.0) + pow(data->player_y - ray->next_vertical_y, 2.0)); // Вычисляем расстояние до пересечения
        ray->texture_x = ray->next_vertical_y - (int) ray->next_vertical_y; // Вычисляем точку пересечения по текстуре
        if (ray->step_x > 0) // Если шаг по X положительный
            ray->texture_x = 1 - ray->texture_x; // Инвертируем текстурную координату по X
    } 
    else
        ray->vertical_distance = INFINITY; // Если шаг по X равен нулю, расстояние до пересечения по вертикали бесконечно
    
    if (ray->step_y != 0) // Если шаг по Y не равен нулю
    {
        ray->next_horizontal_x = data->player_x + ray->direction_x / ray->direction_y * (ray->next_horizontal_y - data->player_y); // Вычисляем пересечение горизонтальной линии
        ray->horizontal_distance = sqrt(pow(data->player_x - ray->next_horizontal_x, 2.0) + pow(data->player_y - ray->next_horizontal_y, 2.0)); // Вычисляем расстояние до пересечения
        ray->texture_y = ray->next_horizontal_x - (int) ray->next_horizontal_x; // Вычисляем точку пересечения по текстуре
        if (ray->step_y < 0) ray->texture_y = 1 - ray->texture_y; // Если шаг по Y отрицательный, инвертируем текстурную координату по Y
    }
    else
        ray->horizontal_distance = INFINITY; // Если шаг по Y равен нулю, расстояние до пересечения по горизонтали бесконечно
}

float handle_check(t_data *data, Ray *ray, int flag)
{
    // Вывод значений до вычислений
    // printf("Before check: map_x = %d, map_y = %d, next_vertical_x = %f, next_vertical_y = %f, next_horizontal_x = %f, next_horizontal_y = %f\n", 
    //    ray->map_x, ray->map_y, ray->next_vertical_x, ray->next_vertical_y, ray->next_horizontal_x, ray->next_horizontal_y);

    // Обновление координат в зависимости от флага
    if(flag == 1) // Если флаг равен 1, проверяем вертикальное пересечение
    {
        ray->map_x = (int)ray->next_vertical_x; // Обновляем координаты карты для вертикального пересечения
        ray->map_y = (int)ray->next_vertical_y;
    }
    else // Если флаг не равен 1, проверяем горизонтальное пересечение
    {
        ray->map_y = (int)ray->next_horizontal_y; // Обновляем координаты карты для горизонтального пересечения
        ray->map_x = (int)ray->next_horizontal_x;
    }

    // Вывод значений после вычислений
    printf("After check: map_x = %d, map_y = %d\n", ray->map_x, ray->map_y);

    // Проверка на выход за пределы карты
    if (ray->map_x < 0 || ray->map_x >= data->map_width || ray->map_y < 0 || ray->map_y >= data->map_height) // Если координаты за пределами карты
    {
        printf("Error: out of bounds array access\n"); // Выводим ошибку
        printf("Out of bounds: map_x = %d, map_y = %d\n", ray->map_x, ray->map_y); // Выводим точные координаты
        return (-1); // Возвращаем ошибку
    }
    return (0); // Успешная проверка
}

float handle_vertical_intersection(t_data *data, Ray *ray)
{
    int texture_index;
    int map_x_offset;

    // Отладка: Выводим текущие координаты и шаги
   // printf("handle_vertical_intersection: ray->map_x = %d, ray->map_y = %d\n", ray->map_x, ray->map_y);
    printf("ray->step_x = %d, ray->step_y = %d\n", ray->step_x, ray->step_y);

    if (handle_check(data, ray, 1) == -1) // Проверяем, если пересечение за пределами карты
    {
        printf("Out of bounds detected\n");
        return (-1); // Возвращаем ошибку, если за пределами
    }

    // Отладка: Выводим сдвиг по X
    if (ray->step_x > 0) // Если шаг по X положительный
    {
        map_x_offset = 0; // Не сдвигаем индекс по X
        printf("map_x_offset = 0 (step_x > 0)\n");
    }
    else
    {
        map_x_offset = -1; // Сдвигаем индекс по X влево, если шаг отрицательный
        printf("map_x_offset = -1 (step_x < 0)\n");
    }

    // Отладка: Проверяем значение в карте
    printf("Checking map[%d][%d + %d] = %c\n", ray->map_y, ray->map_x, map_x_offset, data->new_map[ray->map_y][ray->map_x + map_x_offset]);

    if ((data->new_map[ray->map_y][ray->map_x + map_x_offset] == '1') || (data->new_map[ray->map_y][ray->map_x + map_x_offset] == 'X')) // Если мы столкнулись с стеной
    {
        if (ray->step_x > 0) // Если шаг по X положительный
        {
            texture_index = 1; // Присваиваем индекс текстуры для стены
            printf("Texture index = 1 (step_x > 0)\n");
        }
        else
        {
            texture_index = 3; // Присваиваем индекс текстуры для стены с другой стороны
            printf("Texture index = 3 (step_x < 0)\n");
        }
        
        // Отладка: Сохраняем информацию о текстуре
        printf("Saving texture info: vertical_distance = %.3f, texture_index = %d, texture_x = %.3f\n", ray->vertical_distance, texture_index, ray->texture_x);
        
        return (save_texture_info(data, ray->vertical_distance, texture_index, ray->texture_x)); // Сохраняем информацию о текстуре и возвращаем расстояние
    }

    // Отладка: Шаги при продолжении
    printf("No wall hit, continuing to next intersection\n");
    ray->next_vertical_x += ray->step_x; // Шаг по X для следующего пересечения
    ray->next_vertical_y += ray->step_y; // Шаг по Y для следующего пересечения
    printf("Next intersection: next_vertical_x = %.3f, next_vertical_y = %.3f\n", ray->next_vertical_x, ray->next_vertical_y);

    return (0); // Продолжаем вычисления
}

float handle_horizontal_intersection(t_data *data, Ray *ray)
{
    int texture_index;
    int map_y_offset;

    
    printf("handle_horizontal_intersection: ray->map_x = %d, ray->map_y = %d\n", ray->map_x, ray->map_y);
    printf("ray->step_x = %d, ray->step_y = %d\n", ray->step_x, ray->step_y);

    if (handle_check(data, ray, 0) == -1) // Проверяем, если пересечение за пределами карты
    {
        printf("Out of bounds detected\n");
        return (-1); // Возвращаем ошибку, если за пределами
    }

    // Отладка: Выводим сдвиг по Y
    if (ray->step_y > 0) // Если шаг по Y положительный
    {
        map_y_offset = 0; // Не сдвигаем индекс по Y
        printf("map_y_offset = 0 (step_y > 0)\n");
    }
    else
    {
        map_y_offset = -1; // Сдвигаем индекс по Y вниз, если шаг отрицательный
        printf("map_y_offset = -1 (step_y < 0)\n");
    }

    // Отладка: Проверяем значение в карте
    printf("Checking map[%d + %d][%d] = %c\n", ray->map_y, map_y_offset, ray->map_x, data->new_map[ray->map_y + map_y_offset][ray->map_x]);

    if ((data->new_map[ray->map_y + map_y_offset][ray->map_x] == '1') || (data->new_map[ray->map_y + map_y_offset][ray->map_x] == 'X')) // Если столкнулись с вертикальной стеной
    {
        if (ray->step_y > 0) // Если шаг по Y положительный
        {
            texture_index = 2; // Присваиваем индекс текстуры для стены
            printf("Texture index = 2 (step_y > 0)\n");
        }
        else
        {
            texture_index = 0; // Присваиваем индекс текстуры для стены с другой стороны
            printf("Texture index = 0 (step_y < 0)\n");
        }

        // Отладка: Сохраняем информацию о текстуре
        printf("Saving texture info: horizontal_distance = %.3f, texture_index = %d, texture_y = %.3f\n", ray->horizontal_distance, texture_index, ray->texture_y);

        return (save_texture_info(data, ray->horizontal_distance, texture_index, ray->texture_y)); // Сохраняем информацию о текстуре и возвращаем расстояние
    }

    // Отладка: Шаги при продолжении
    printf("No wall hit, continuing to next intersection\n");
    ray->next_horizontal_x += ray->step_x; // Шаг по X для следующего пересечения
    ray->next_horizontal_y += ray->step_y; // Шаг по Y для следующего пересечения
    printf("Next intersection: next_horizontal_x = %.3f, next_horizontal_y = %.3f\n", ray->next_horizontal_x, ray->next_horizontal_y);

    return (0); // Продолжаем вычисления
}


float trace_ray(t_data *data, float angle)
{
    Ray ray = {0}; // Обнуляем всю структуру

    initialize_ray(data, &ray, angle); // Инициализируем луч с начальной позицией и углом
    while (1) // Бесконечный цикл для поиска пересечений
    {
        calculate_next_intersection(data, &ray); //201
        if (ray.vertical_distance < ray.horizontal_distance) // Используем точку, а не указатель  //201
        {
            int check_x = (ray.step_x == 1) ? ray.next_vertical_x : ray.next_vertical_x - 1;
            printf("11Next intersection: next_vertical_x = %d, check = %d\n\n", (int)ray.next_vertical_x, check_x);
            printf("11pos x = %f, posy = %f", data->player_x, data->player_y);
            if (data->new_map[(int)ray.next_vertical_y][(int)check_x] == '1')
            {
                // Если точка является стеной, сохраняем информацию о цвете
                printf("MATCH\n");
                return save_texture_info(data, ray.vertical_distance, ray.step_x + 1, ray.texture_x); 
            }
            else
            {
                // Если точка не является стеной, двигаем луч дальше
                ray.next_vertical_x += ray.step_x;
                ray.next_vertical_y += ray.step_x * tan(angle);
                printf("1!!Next intersection: next_vertical_x = %d, next_vertcal_y = %d\n\n", (int)ray.next_vertical_x, (int)ray.next_vertical_y);
                
            }
        }
        // Если горизонтальное пересечение ближе
        else
        {
            // Проверяем, является ли точка стеной
            int check_y = (ray.step_y == 1) ? ray.next_horizontal_y : ray.next_horizontal_y - 1;
            printf("22Next intersection: next_horizontal_x = %d, check = %d\n", (int)ray.next_horizontal_x, check_y);
            printf("22pos x = %f, posy = %f", data->player_x, data->player_y);
            if (data->new_map[(int)check_y][(int)ray.next_horizontal_x] == '1')
            {
                // Если точка является стеной, сохраняем информацию о цвете
               printf("MATCH\n");
                return save_texture_info(data, ray.horizontal_distance, ray.step_y + 2, ray.texture_y); 
            }
            else
            {
                // Если точка не является стеной, двигаем луч дальше
                ray.next_horizontal_y += ray.step_y;
                ray.next_horizontal_x += ray.step_y / tan(angle);
                printf("2!!Next intersection: next_vertical_x = %d, next_vertcal_y = %d\n\n", (int)ray.next_vertical_x, (int)ray.next_vertical_y);

            }
        }
    }
}

