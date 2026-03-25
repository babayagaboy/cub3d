/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:00:20 by myivanov          #+#    #+#             */
/*   Updated: 2026/03/25 14:24:41 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	count_elements(char **cub, int y)
{
	int	count;

	count = 0;
	while (cub[y])
	{
		if (cub[y] && (ft_isempty(cub[y]) || cub[y][0] == '\n'))
		{
			y++;
			continue;
		}
		count++;
		if (ft_strnstr(ft_findspace(cub[y]), "C", 1))
			break ;
		y++;
	}
	return (count);
}

int	process_line(char *line, char **elements_file, int i, int *stop)
{
	char	*clean;

	clean = ft_findspace(line);
	if (ft_strnstr(clean, "C", 1))
		*stop = 1;
	elements_file[i] = looksmax_string(clean);
	if (!elements_file[i])
		return (0);
	return (1);
}

char	**fill_elements(char **cub, int *y, int count)
{
	char	**elements_file;
	int		i;
	int		stop;

	elements_file = malloc(sizeof(char *) * (count + 2));
	if (!elements_file)
		return (NULL);
	i = 0;
	stop = 0;
	while (cub[*y])
	{
		if (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n'))
		{
			(*y)++;
			continue;
		}
		if (!process_line(cub[*y], elements_file, i, &stop))
			return (free_char_arr(elements_file, i), NULL);
		(*y)++;
		if (stop)
			break ;
		i++;
	}
	elements_file[i + 1] = NULL;
	return (elements_file);
}

char	**get_elements(char **cub, int *y)
{
	char	**elements_file;
	int		count;

	if (!cub)
		return (NULL);
	count = count_elements(cub, *y);
	elements_file = fill_elements(cub, y, count);
	return (elements_file);
}
