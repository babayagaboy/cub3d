/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:07:46 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/14 17:01:47 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft/libft.h"
#include <cub3d.h>

int		*get_player_coords(char **map)
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
int	is_wall(char c)
{
	int	i;
	char	walls[] = {'1', '2', '3', '4', '5'};
	i = 0;

	while (i < 5)
	{
		if (walls[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_player(char c)
{
	int	i;
	char	player[] = {'N', 'S', 'E', 'W'};
	i = 0;

	while (i < 4)
	{
		if (player[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		check_walls(char **map, int y, int x)
{
	if (!map)
		return (0);
	int	count = 0;
	if (y > 0 && map[y - 1] && map[y - 1][x] && (is_wall(map[y - 1][x]) || map[y - 1][x] == '0' || map[y - 1][x] == 'D')) // North
		count++;
	if (map[y + 1] && map[y + 1][x] && (is_wall(map[y + 1][x]) || map[y + 1][x] == '0' || map[y + 1][x] == 'D')) // South
		count++;
	if (x > 0 && map[y][x - 1] && (is_wall(map[y][x - 1]) || map[y][x - 1] == '0' || map[y][x - 1] == 'D')) // West
		count++;
	if (map[y][x + 1] && (is_wall(map[y][x + 1]) || map[y][x + 1] == '0' || map[y][x + 1] == 'D')) // East
		count++;
	if (count == 4)
		return (1);
	printf("[%d][%d] = %d\n", y, x, count);
	return (0);
}

int		check_map_borders(char **map, t_game *g)
{
	int	x;
	int	y;
	int	x_max;

	// topo
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
	// esquerda
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

int		check_map_interior(char **map)
{
	int	y;
	int	x;

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0' && check_walls(map, y, x) == 0)
			{
				printf ("The check wall failed\n");
				return (0);
			}
			if (map[y][x] == 'D' && check_doors(map, y, x) == 0)
			{
				printf ("The check door failed\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

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


int		check_map(char **map, t_player *p, t_game *g)
{
	int	*player_coords;
	char	player_orientation;

	if (!map || !map[0])
		return (0);

	player_coords = get_player_coords(map);
	if (!player_coords)
		return (0);
	player_orientation = map[player_coords[0]][player_coords[1]];
	map[player_coords[0]][player_coords[1]] = '0';
	if (!check_map_borders(map, g) || !check_map_interior(map))
	{
		free(player_coords);
		return (0);
	}
	map[player_coords[0]][player_coords[1]] = player_orientation; //to do (dir_y, dir_x) = get_player_orientation()
	get_player_orientation(player_orientation, p);
	p->pos_y = (double)player_coords[0];
	p->pos_x = (double)player_coords[1];
	free(player_coords);
	return (1);
}
