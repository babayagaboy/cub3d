/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:24:14 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 19:23:16 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_player_orientation(char player_orientation, t_player *p)
{
	if (player_orientation == 'N')
	{
		p->dir_y = -1;
		p->dir_x = 0;
	}
	if (player_orientation == 'S')
	{
		p->dir_y = 1;
		p->dir_x = 0;
	}
	if (player_orientation == 'E')
	{
		p->dir_y = 0;
		p->dir_x = 1;
	}
	if (player_orientation == 'W')
	{
		p->dir_y = 0;
		p->dir_x = -1;
	}
}

int	is_player(char c)
{
	int		i;
	char	player[4];

	player[0] = 'N';
	player[1] = 'S';
	player[2] = 'E';
	player[3] = 'W';
	i = 0;
	while (i < 4)
	{
		if (player[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_walls_doors(char **map, int y, int x)
{
	int	count;

	count = 0;
	if (!map)
		return (0);
	if (y > 0 && map[y - 1] && map[y - 1][x] && (is_wall(map[y - 1][x])
		|| map[y - 1][x] == '0' || map[y - 1][x] == 'D'))
		count++;
	if (map[y + 1] && map[y + 1][x] && (is_wall(map[y + 1][x])
		|| map[y + 1][x] == '0' || map[y + 1][x] == 'D'))
		count++;
	if (x > 0 && map[y][x - 1] && (is_wall(map[y][x - 1])
		|| map[y][x - 1] == '0' || map[y][x - 1] == 'D' ))
		count++;
	if (map[y][x + 1] && (is_wall(map[y][x + 1])
		|| map[y][x + 1] == '0' || map[y][x + 1] == 'D'))
		count++;
	if (count == 4)
		return (1);
	return (0);
}

int	check_doors(char **map, int y, int x)
{
	if (!map)
		return (0);
	if (y > 0 && map[y - 1] && map[y - 1][x] && is_wall(map[y - 1][x]))
		if (map[y + 1] && map[y + 1][x] && is_wall(map[y + 1][x]))
			if (x > 0 && map[y][x - 1] && map[y][x - 1] != ' ')
				if (map[y][x + 1] && map[y][x + 1] != ' ')
					return (1);
	if (x > 0 && map[y][x - 1] && is_wall(map[y][x - 1]))
		if (map[y][x + 1] && is_wall(map[y][x + 1]))
			if (y > 0 && map[y - 1] && map[y - 1][x] && map[y - 1][x] != ' ')
				if (map[y + 1] && map[y + 1][x] && (map[y + 1][x]) != ' ')
					return (1);
	return (0);
}
