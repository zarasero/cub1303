/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:11:01 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 20:04:43 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	is_starting_point(char **map, int i, int j)
{
	if (map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'N')
		return (true);
	else
		return (false);
}

void	check_colors(char *file, t_data *data)
{
	int	i;
	int	coma;

	i = 1;
	coma = 0;
	while (file[i])
	{
		if (file[i] == ',')
		{
			coma++;
			i++;
		}
		else if (file[i] == '-')
			err(data, RGB_SUP);
		else if (file[i] == '\t' || file[i] == ' ' || file[i] == '\n'
			|| (file[i] >= '0' && file[i] <= '9'))
			i++;
		else
			err(data, RGB_COMA_FORMAT);
	}
	if (coma != 2)
		err(data, RGB_COMA_FORMAT);
	return ;
}

void	color_is_valid(int *color, t_data *data)
{
	int	i;

	i = 0;
	if (color)
	{
		while (i < 3)
		{
			if (color[i] > 255)
				err(data, RGB_SUP);
			i++;
		}
	}
	return ;
}

int	skip_whitespaces(char **save, int i, int j, int *start)
{
	while (save[i][j] && (save[i][j] < '0' || save[i][j] > '9'))
		j++;
	*start = j;
	while (save[i][j] && (save[i][j] >= '0' && save[i][j] <= '9'))
		j++;
	return (j);
}
