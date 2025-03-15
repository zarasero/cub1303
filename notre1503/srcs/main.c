/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:23:50 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 19:46:07 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	data->file = NULL;
	data->c_color = NULL;
	data->f_color = NULL;
	data->path_text[0] = NULL;
	data->path_text[2] = NULL;
	data->path_text[1] = NULL;
	data->path_text[3] = NULL;
	data->map = NULL;
	data->new_map = NULL;
	data->x_pos = -1;
	data->y_pos = -1;
	data->map_lines = 0;
	data->map_start = -1;
	data->end_map = -1;
}

void	parsing_cub(char *argv)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		err(data, MALLOC);
	init_data(data);
	if (!is_valid_data_extension(argv))
		err(data, EXTENSION);
	copy_cub_file(argv, data);
	where_is_the_map(data, data->file, &data->map_lines);
	save_map(data, data->file, &data->map, &data->map_lines);
	extract_textures(data);
	extract_valid_colors(data);
	if (are_colors_and_textures_before_map(data, 0) == false)
		err(data, TXT_AFTER_MAP);
	file_is_clean(data);
	parsing_map(data);
	part_2(data);
	//free_all(data);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	parsing_cub(argv[1]);
	return (0);
}
