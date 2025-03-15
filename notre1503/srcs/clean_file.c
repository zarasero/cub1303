/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:08:33 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 19:29:16 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	line_is_not_texture(t_data *data, int i, int *checker)
{
	if (ft_strncmp(data->file[i], "NO", 2) == 0)
	{
		(*checker)++;
		return (false);
	}
	else if (ft_strncmp(data->file[i], "SO", 2) == 0)
	{
		(*checker)++;
		return (false);
	}
	else if (ft_strncmp(data->file[i], "WE", 2) == 0)
	{
		(*checker)++;
		return (false);
	}
	else if (ft_strncmp(data->file[i], "EA", 2) == 0)
	{
		(*checker)++;
		return (false);
	}
	else
		return (true);
}

bool	line_is_not_color(t_data *data, int i, int *checker)
{
	if (ft_strncmp(data->file[i], "F", 1) == 0)
	{
		(*checker)++;
		return (false);
	}
	else if (ft_strncmp(data->file[i], "C", 1) == 0)
	{
		(*checker)++;
		return (false);
	}
	else
		return (true);
}

bool	line_is_not_empty(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->file[i][j])
	{
		if (data->file[i][j] != ' ' && data->file[i][j] != '\t'
			&& data->file[i][j] != '\n')
			return (true);
		j++;
	}
	return (false);
}

bool	file_is_clean(t_data *data)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (i < data->map_start)
	{
		if (line_is_not_texture(data, i, &checker)
			&& line_is_not_color(data, i, &checker)
			&& line_is_not_empty(data, i))
			err(data, CLEAN);
		i++;
	}
	if (checker != 6)
		err(data, CLEAN);
	file_end_is_clean(data);
	return (true);
}

void	file_end_is_clean(t_data *data)
{
	int	i;
	int	j;

	i = data->end_map;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j])
		{
			if (data->file[i][j] != ' ' && data->file[i][j] != '\t'
				&& data->file[i][j] != '\n' && data->file[i][j] != '\0')
				err(data, CLEAN);
			j++;
		}
		i++;
	}
	return ;
}
