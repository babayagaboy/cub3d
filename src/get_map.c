/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:56:23 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/14 16:09:00 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	get_map_bounds(char **cub, int *y)
{
	int	count;
	int	k;

	while (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n'))
		(*y)++;
	k = *y;
	count = 0;
	while (cub[k] && !(ft_isempty(cub[k]) || cub[k][0] == '\n'))
	{
		count++;
		k++;
	}
	return (count);
}

char	**copy_map(char **cub, int start, int count)
{
	char	**map;
	int		i;
	int		k;

	map = ft_calloc(count + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	k = start;
	while (i < count && cub[k])
	{
		map[i] = ft_calloc(ft_strlen(cub[k]) + 1, sizeof(char));
		if (!map[i])
			return (free_char_arr(map, i), NULL);
		ft_strlcpy(map[i], cub[k], ft_strlen(cub[k]) + 1);
		i++;
		k++;
	}
	map[i] = NULL;
	return (map);
}

char	**get_map(char **cub, int *y, t_game *g)
{
	int		count;
	char	**map;

	if (!cub)
		return (NULL);
	count = get_map_bounds(cub, y);
	map = copy_map(cub, *y, count);
	g->map_h = count;
	return (map);
}
