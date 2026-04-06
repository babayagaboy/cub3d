/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:00:20 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/06 15:49:16 by myivanov         ###   ########.fr       */
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
		if (count == 7)
			break ;
		y++;
	}
	return (count);
}

int	process_line(char *line, char **elements_file, int i, int *stop)
{
	char	*clean;

	clean = ft_findspace(line);
	if (i > 6)
	{
		*stop = 1;
		return (1);
	}
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

	elements_file = ft_calloc(count + 2, sizeof(char *));
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
		if (stop)
			break ;
		(*y)++;
		i++;
	}
	elements_file[i] = NULL;
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
