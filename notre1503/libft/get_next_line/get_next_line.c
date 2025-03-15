/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobonill <mobonill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:20:40 by mobonill          #+#    #+#             */
/*   Updated: 2025/02/06 18:10:40 by mobonill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*new_rest(char *rest, char *line)
{
	int		len_rest;
	int		len_line;
	int		i;
	char	*str;

	i = 0;
	len_rest = ft_strlen(rest);
	len_line = ft_strlen(line);
	if ((len_rest - len_line) == 0)
	{
		free(rest);
		return (NULL);
	}
	str = malloc(sizeof(char) * ((len_rest - len_line) + 1));
	if (!str)
		return (NULL);
	while (i < (len_rest - len_line))
	{
		str[i] = rest[len_line + i];
		i++;
	}
	str[i] = '\0';
	free(rest);
	return (str);
}

char	*read_line(char *rest)
{
	int		i;
	char	*str;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		str[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
	{
		str[i] = rest[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char	*rest_join(char *rest, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(rest, buffer);
	free(rest);
	return (temp);
}*/

char	*read_tous_line(int fd, char *rest)
{
	char	*buffer;
	int		byte_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0 && (!rest || !ft_strchr(rest, '\n')))
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (byte_read == 0)
		{
			free(buffer);
			return (rest);
		}
		buffer[byte_read] = '\0';
		rest = ft_strjoin_gnl(rest, buffer);
	}
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	rest = read_tous_line(fd, rest);
	if (!rest)
		return (NULL);
	line = read_line(rest);
	rest = new_rest(rest, line);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	int fd;
// 	char *line;

// 	if (argc < 2)
// 	{
// 		argv[1] = "";
// 	}
// 	fd = open("fd.txt", O_RDONLY);
// 	for (int i = 0; i < atoi(argv[1]); ++i)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }