#include "../include/cub3d.h"

void toggle_door(t_data *data)
{
    int px = (int)data->player.x;
    int py = (int)data->player.y;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx = px + dx;
            int ny = py + dy;

            if (nx >= 0 && ny >= 0 && ny < data->map_height && nx < data->map_width)
            {
                if (data->map[ny][nx] == 'D' && fabs(data->player.x - nx) < 1.2 && fabs(data->player.y - ny) < 1.2)
                {
                    data->doors[ny][nx] = !data->doors[ny][nx];
                    return;
                }
            }
        }
    }
}
