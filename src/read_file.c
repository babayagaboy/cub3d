/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:37:20 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/05 23:42:29 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

char	*read_into_buffer(char *file)
{
	char	*buff;
	int		fd;
	int		i;
	int		num_read;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	buff = malloc(sizeof(char) * 100000);
	if (!buff)
		return (NULL);
	i = 0;
	num_read = read(fd, &buff[i], 1);
	if (num_read == -1)
		return (free(buff), NULL);
	while (num_read > 0 && i < 99998)
		num_read = read(fd, &buff[++i], 1);
	buff[i] = '\0';
	close(fd);
	return (buff);
}

int	count_lines(char *buff, int size)
{
	int	count;
	int	j;

	count = 0;
	j = 0;
	while (buff[j])
	{
		if (buff[j] == '\n')
			count++;
		j++;
	}
	if (size > 0 && buff[size - 1] != '\n')
		count++;
	return (count);
}

char	*extract_line(char *buff, int *j)
{
	int		start;
	int		len;
	char	*line;

	start = *j;
	len = 0;
	while (buff[*j] && buff[*j] != '\n')
	{
		len++;
		(*j)++;
	}
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, &buff[start], len + 1);
	if (buff[*j] == '\n')
		(*j)++;
	return (line);
}

char	**split_lines(char *buff, int count)
{
	char	**map;
	int		j;
	int		k;

	map = ft_calloc(count + 1, sizeof(char *));
	if (!map)
		return (NULL);
	j = 0;
	k = 0;
	while (buff[j] && k < count)
	{
		map[k] = extract_line(buff, &j);
		if (!map[k])
			return (free_char_arr(map, k), NULL);
		k++;
	}
	map[k] = NULL;
	return (map);
}

char	**read_file(char *file)
{
	char	*buff;
	char	**map;
	int		count;
	int		size;

	buff = read_into_buffer(file);
	if (!buff)
		return (NULL);
	size = ft_strlen(buff);
	count = count_lines(buff, size);
	map = split_lines(buff, count);
	free(buff);
	return (map);
}
