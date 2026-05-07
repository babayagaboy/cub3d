/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:07:46 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 19:20:27 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft/libft.h"
#include <cub3d.h>

int	*get_player_coords(char **map)
{
	int	*player_coord;
	int	count;

	if (!map)
		return (NULL);
	player_coord = malloc(sizeof(int) * 2);
	if (!player_coord)
		return (NULL);
	count = find_player(map, player_coord);
	if (count != 1)
		return (free(player_coord), NULL);
	return (player_coord);
}

int	check_walls(char **map, int y, int x)
{
	int	count;

	count = 0;
	if (!map)
		return (0);
	if (y > 0 && map[y - 1] && map[y - 1][x]
		&& (is_wall(map[y - 1][x]) || map[y - 1][x] == '0'))
		count++;
	if (map[y + 1] && map[y + 1][x]
		&& (is_wall(map[y + 1][x]) || map[y + 1][x] == '0'))
		count++;
	if (x > 0 && map[y][x - 1]
		&& (is_wall(map[y][x - 1]) || map[y][x - 1] == '0'))
		count++;
	if (map[y][x + 1] && (is_wall(map[y][x + 1]) || map[y][x + 1] == '0'))
		count++;
	if (count == 4)
		return (1);
	return (0);
}

int	check_map_interior(char **map, t_ele_var *vars)
{
	int	y;
	int	x;

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x] != '\0')
		{
			if (vars->door_found == 1)
			{
				if ((map[y][x] == '0' && check_walls_doors(map, y, x) == 0)
					|| (map[y][x] == 'D' && check_doors(map, y, x) == 0))
					return (0);
			}
			else
			{
				if (map[y][x] == '0' && check_walls(map, y, x) == 0)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map(char **map, t_player *p, t_game *g, t_ele_var *vars)
{
	int		*player_coords;
	char	player_orientation;

	if (!map || !map[0])
		return (0);
	player_coords = get_player_coords(map);
	if (!player_coords)
		return (0);
	player_orientation = map[player_coords[0]][player_coords[1]];
	map[player_coords[0]][player_coords[1]] = '0';
	if (!check_map_borders(map, g) || !check_map_interior(map, vars))
	{
		printf("Error\nInvalid map\n");
		free(player_coords);
		return (0);
	}
	map[player_coords[0]][player_coords[1]] = player_orientation;
	get_player_orientation(player_orientation, p);
	p->pos_y = (double)player_coords[0];
	p->pos_x = (double)player_coords[1];
	free(player_coords);
	return (1);
}
