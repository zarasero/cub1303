/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:21:50 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 19:45:48 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_valid_data_extension(char *argv)
{
	int	i;

	i = ft_strlen(argv);
	if (i < 5)
		return (false);
	if (argv[i - 1] == 'b' && argv[i - 2] == 'u'
		&& argv[i - 3] == 'c' && argv[i - 4] == '.')
		return (true);
	return (false);
}

void	copy_cub_file(char *argv, t_data *data)
{
	int		i;
	int		fd;
	char	*line;

	line = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		free(line);
		err(data, OPENFD);
	}
	i = count_lines_fd(argv);
	data->file = malloc(sizeof(char *) * (i + 1));
	if (!data->file)
		err(data, MALLOC);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		data->file[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	data->file[i] = NULL;
	close(fd);
}

void	where_is_the_map(t_data *data, char **file, int *map_lines)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t')
			j++;
		if (file[i][j] == '1' || file[i][j] == '0')
		{
			if (data->map_start == -1)
				data->map_start = i;
			(*map_lines)++;
		}
		else if (data->map_start != -1)
			break ;
		i++;
	}
	if (data->map_start == -1 || *map_lines < 3)
		err(data, MAP_INVALID);
	data->end_map = data->map_start + *map_lines;
}

void	save_map(t_data *data, char **file, char ***map, int *map_lines)
{
	int	i;

	*map = (char **)malloc(sizeof(char *) * (*map_lines + 1));
	if (!*map)
		err(data, MALLOC);
	i = 0;
	while (i < *map_lines)
	{
		(*map)[i] = ft_strdup(file[data->map_start + i]);
		if (!(*map)[i])
			err(data, MALLOC);
		i++;
	}
	(*map)[i] = NULL;
}

void	check_starting_point(char **map, int map_lines, t_data *data, int j)
{
	int	i;

	i = -1;
	while (++i < map_lines && map[i])
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] != ' ' && map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != '\t' && map[i][j] != '\0' && map[i][j] != '\n')
			{
				if (is_starting_point(map, i, j) == true)
				{
					if (data->x_pos != -1)
						err(data, STARTING_POINT);
					data->x_pos = i + 1;
					data->y_pos = j + 1;

											// add
					if (map[i][j] == 'E')
						data->player_angle = 0;
					else if (map[i][j] == 'N')
						data->player_angle = M_PI / 2;
					else if (map[i][j] == 'W')
						data->player_angle = M_PI;
					else if (map[i][j] == 'S')
						data->player_angle = 3 * M_PI / 2;
					return;
				}
				else
					err(data, CHAR_NOT_VALID);
			}
		}
	}
	if (data->x_pos == 0 && data->y_pos == 0)
		err(data, STARTING_POINT);
}
