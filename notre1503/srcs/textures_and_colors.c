/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_and_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:47:29 by mobonill          #+#    #+#             */
/*   Updated: 2025/02/06 20:06:53 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*find_textures_paths(char *file, t_data *data)
{
	int		j;
	int		len;
	int		start;
	char	*txt;

	j = 0;
	len = 0;
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	j += 2;
	if (file[j] != '\t' && file[j] != ' ')
		err(data, ID_TXT);
	while (file[j] && (file[j] == '\t' || file[j] == ' '))
		j++;
	if (file[j] == '\n' && file[j + 1] == '\0')
		return (err(data, ID_TXT), NULL);
	start = j;
	while (file[j] && file[j] != '\n') //modif
	{
		len++;
		j++;
	}
	txt = ft_substr(file, start, len);
	return (txt);
}

void	extract_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "NO", 2) == 0 && !data->path_text[0])
			data->path_text[0] = find_textures_paths(data->file[i], data);
		else if (ft_strncmp(data->file[i], "SO", 2) == 0 && !data->path_text[2])
			data->path_text[2] = find_textures_paths(data->file[i], data);
		else if (ft_strncmp(data->file[i], "WE", 2) == 0 && !data->path_text[3])
			data->path_text[3] = find_textures_paths(data->file[i], data);
		else if (ft_strncmp(data->file[i], "EA", 2) == 0 && !data->path_text[1])
			data->path_text[1] = find_textures_paths(data->file[i], data);
		i++;
	}
}

int	*find_rgb_colors(char *file, int *colors, int k, t_data *data)
{
	char	**save;
	char	*parsed;
	int		j;
	int		start;
	int		i;

	i = -1;
	save = ft_split(file, ',');
	colors = malloc(sizeof(int) * 3);
	while (save[++i])
	{
		j = skip_whitespaces(save, i, 0, &start);
		if ((j - start) > 0)
		{
			if ((j - start) > 3)
				error_color(colors, save, data);
			parsed = ft_substr(save[i], start, j - start);
			colors[k++] = ft_atoi(parsed);
			free(parsed);
		}
	}
	return (free_char_tab(save), colors);
}

void	extract_valid_colors(t_data *data)
{
	int	i;

	i = 0;
	while (data->file[i] && i < data->map_start)
	{
		if (ft_strncmp(data->file[i], "F", 1) == 0)
		{
			check_colors(data->file[i], data);
			data->f_color = find_rgb_colors(data->file[i],
					data->f_color, 0, data);
			color_is_valid(data->f_color, data);
		}
		else if (ft_strncmp(data->file[i], "C", 1) == 0)
		{
			check_colors(data->file[i], data);
			data->c_color = find_rgb_colors(data->file[i],
					data->c_color, 0, data);
			color_is_valid(data->c_color, data);
		}
		i++;
	}
}

bool	are_colors_and_textures_before_map(t_data *data, int j)
{
	int	i;

	i = -1;
	while (data->file[++i])
	{
		j = 0;
		while (data->file[i][j] == ' ' || data->file[i][j] == '\t')
			j++;
		if (data->file[i][j] == '1')
		{
			while (data->file[i][j] && (data->file[i][j] == '1'
				|| data->file[i][j] == ' ' || data->file[i][j] == '\t'
				|| data->file[i][j] == '\n'))
				j++;
			if (data->file[i][j] == '\0')
			{
				if (data->path_text[0] && data->path_text[2] && data->path_text[3]
					&& data->path_text[1] && data->c_color && data->f_color)
					return (true);
				else
					return (false);
			}
		}
	}
	return (false);
}