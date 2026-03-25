/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:43:32 by myivanov          #+#    #+#             */
/*   Updated: 2026/03/25 13:49:24 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	check_rbg(char *str)
{
	char	**splited;
	char	c[] = {',', '\0'};
	int		result;

	if (!str)
		return (0);
	splited = ft_split(str, c);
	if (!splited)
		return (0);
	result = validate_rgb_values(splited);
	free_memory(splited);
	return (result);
}

int	handle_texture(char *line, int value, int *elements_found, int *opened)
{
	int	fd;

	fd = open(&line[5], O_RDONLY);
	*elements_found += value;
	if (fd >= 0)
	{
		*opened += value;
		close(fd);
	}
	return (1);
}

int	handle_floor_ceiling(char *line, int value,
		int *elements_found, int *f_c_element)
{
	int	type;
	int	fd;
	int	increment;

	*elements_found += value;
	type = f_c_type(&line[2]);
	if (value == 5)
		increment = 1;
	else
		increment = 2;
	if (type == 2)
	{
		fd = open(&line[4], O_RDONLY);
		if (fd >= 0)
		{
			*f_c_element += increment;
			close(fd);
		}
	}
	else
	{
		if (check_rbg(&line[2]))
			*f_c_element += increment;
	}
	return (1);
}

void	process_element_line(char *line, int *elements_found,
							int *opened, int *f_c_element)
{
	if (ft_strncmp(line, "NO", 2) == 0 && line[2] == ' ')
		handle_texture(line, 1, elements_found, opened);
	else if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
		handle_texture(line, 2, elements_found, opened);
	else if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
		handle_texture(line, 3, elements_found, opened);
	else if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
		handle_texture(line, 4, elements_found, opened);
	else if (ft_strncmp(line, "F", 1) == 0 && line[1] == ' ')
		handle_floor_ceiling(line, 5, elements_found, f_c_element);
	else if (ft_strncmp(line, "C", 1) == 0 && line[1] == ' ')
		handle_floor_ceiling(line, 6, elements_found, f_c_element);
}

int	check_elements(char **elements)
{
	int	y;
	int	elements_found;
	int	opened;
	int	f_c_element;

	if (!elements)
		return (0);
	y = 0;
	elements_found = 0;
	opened = 0;
	f_c_element = 0;
	while (elements[y])
	{
		process_element_line(elements[y],
			&elements_found, &opened, &f_c_element);
		y++;
	}
	if (elements_found == 21 && opened == 10 && f_c_element == 3)
		return (1);
	return (0);
}


