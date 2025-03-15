/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:38:28 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 20:03:54 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

void	free_all(t_data *data)
{
	if (data == NULL)
		return ;
	if (data->c_color != NULL)
		free(data->c_color);
	if (data->f_color != NULL)
		free(data->f_color);
	if (data->path_text[1] != NULL)
		free(data->path_text[1]);
	if (data->path_text[0] != NULL)
		free(data->path_text[0]);
	if (data->path_text[2] != NULL)
		free(data->path_text[2]);
	if (data->path_text[3] != NULL)
		free(data->path_text[3]);
	if (data->map)
		free_char_tab(data->map);
	if (data->new_map)
		free_char_tab(data->new_map);
	if (data->file)
		free_char_tab(data->file);
	free(data);
}

void	error_color(int *colors, char **save, t_data *data)
{
	free(colors);
	free_char_tab(save);
	err(data, RGB_SUP);
}
