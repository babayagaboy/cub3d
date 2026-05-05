/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:26:25 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/05 23:31:07 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_wall(char c)
{
	int		i;
	char	wall;

	i = 0;
	wall = '1';
	while (i < 5)
	{
		if (wall == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_map_borders(char **map, t_game *g)
{
	int	x;
	int	y;
	int	x_max;

	x = 0;
	x_max = x;
	while (map[0][x] != '\0')
	{
		if (map[0][x] == '0' || map[0][x] == 'D')
			return (0);
		x++;
		if (x > x_max)
			x_max = x;
	}
	y = 0;
	while (map[y])
	{
		if (map[y][0] == '0' || map[y][0] == 'D')
			return (0);
		y++;
	}
	g->map_w = x_max;
	return (1);
}
