/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:24:05 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 19:36:31 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parsing_map(t_data *data)
{
	int		max_len;
	char	*x_lines;

	x_lines = NULL;
	check_starting_point(data->map, data->map_lines, data, 0);
	max_len = map_line_max_lenght(data->map);
	x_lines = create_first_and_bottom_lines(max_len, x_lines, data);
	data->new_map = create_new_map(data, max_len, data->new_map, x_lines);
	if (is_map_closed(data->new_map, max_len + 1, data->map_lines + 2, 0)
		== false)
		err(data, MAP_OPENED);
	data->map_width = (max_len + 1);
	print_char_tab(data->new_map);
}

char	*create_first_and_bottom_lines(int max_len, char *x_lines, t_data *data)
{
	int	j;

	j = 0;
	x_lines = malloc(sizeof(char) * (max_len + 3));
	if (!x_lines)
		err(data, MALLOC);
	while (j <= max_len)
	{
		x_lines[j] = 'X';
		j++;
	}
	x_lines[j] = '\0';
	return (x_lines);
}

char	*fill_line(char *map, int len, int i)
{
	char	*res;
	int		j;

	j = 1;
	res = malloc(sizeof(char) * (len + 3));
	res[0] = 'X';
	while (map[i])
	{
		if (map[i] == '1' || map[i] == '0')
			res[j] = map[i];
		else if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W'
			|| map[i] == 'E')
			res[j] = map[i];
		else
			res[j] = 'X';
		j++;
		i++;
	}
	while (j <= len)
	{
		res[j] = 'X';
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	**create_new_map(t_data *data, int max_len, char **new_map,
	char *x_lines)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	new_map = malloc(sizeof(char *) * (data->map_lines + 3));
	new_map[0] = x_lines;
	while (data->map[i])
	{
		new_map[j] = fill_line(data->map[i], max_len, 0);
		j++;
		i++;
	}
	new_map[j] = ft_strdup(x_lines);
	new_map[j + 1] = NULL;
	return (new_map);
}

bool	is_map_closed(char **map, int len, int rows, int i)
{
	int	j;

	while (i < rows)
	{
		j = 0;
		while (j < len)
		{
			if (is_starting_point(map, i, j) == true || map[i][j] == '0')
			{
				if (i == 0 || j == 0 || i == rows || j == len - 1)
					return (false);
				if (i > 0 && !is_valid_char(map[i - 1][j]))
					return (false);
				if (i < rows - 1 && !is_valid_char(map[i + 1][j]))
					return (false);
				if (j > 0 && !is_valid_char(map[i][j - 1]))
					return (false);
				if (j < len - 1 && !is_valid_char(map[i][j + 1]))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
