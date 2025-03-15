/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:01:10 by morgane           #+#    #+#             */
/*   Updated: 2025/02/06 19:29:57 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return ;
}

void	err(t_data *data, char *str)
{
	while (*str)
		write(2, str++, 1);
	free_all(data);
	exit(1);
}

int	count_lines_fd(char *argv)
{
	char	*line;
	int		len;
	int		fd;

	line = NULL;
	len = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		err(NULL, OPENFD);
	line = get_next_line(fd);
	while (line != NULL)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

int	map_line_max_lenght(char **map)
{
	int		i;
	size_t	max;
	size_t	len;

	i = 0;
	max = 0;
	len = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return ((int)max);
}

bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'S' || c == 'W'
		|| c == 'E' || c == 'N');
}
