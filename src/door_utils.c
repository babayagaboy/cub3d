/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 23:59:13 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/06 23:59:13 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	hit_door_plane_y(t_ray *r, t_player *p, t_door *door)
{
	double	door_plane;
	double	hit_pos;
	double	local_pos;

	if (r->ray_dir_y == 0)
		return (0);
	door_plane = r->map_y + 0.5;
	r->perp_wall_dist = (door_plane - p->pos_y) / r->ray_dir_y;
	hit_pos = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
	local_pos = hit_pos - r->map_x;
	if (r->perp_wall_dist > 0 && local_pos >= 0.0
		&& local_pos <= (1.0 - door->open_pct))
	{
		r->wall_hit_pos_x = local_pos + door->open_pct;
		return (1);
	}
	return (0);
}

int	hit_door_plane(t_ray *r, t_player *p, t_game *g)
{
	t_door	*door;

	door = find_door(g, r->map_y, r->map_x);
	if (!door || door->open_pct >= 1.0)
		return (0);
	r->door_side = get_door_side(g->map, r->map_y, r->map_x);
	if (r->door_side == 0)
		return (hit_door_plane_x(r, p, door));
	else
		return (hit_door_plane_y(r, p, door));
}

int	get_door_count(char **map)
{
	int	y;
	int	x;
	int	doors;

	if (!map || !map[0])
		return (0);
	y = 0;
	doors = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
				++doors;
			++x;
		}
		++y;
	}
	return (doors);
}

void	fill_door_cords(t_door **door, char **map)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'D')
			{
				door[i]->pos_y = y;
				door[i]->pos_x = x;
				door[i]->open_pct = 0.0;
				door[i]->opening = 0;
				++i;
			}
			++x;
		}
		++y;
	}
}

t_door	**get_door_coords(t_game *g, char **map)
{
	t_door	**door;
	int		i;
	int		door_count;

	i = 0;
	door_count = get_door_count(map);
	door = malloc(sizeof(t_door *) * (door_count + 1));
	if (!door)
		return (NULL);
	while (i < door_count)
	{
		door[i] = malloc(sizeof(t_door));
		if (!door[i])
		{
			while (--i)
				free(door[i]);
			return (NULL);
		}
		++i;
	}
	door[door_count] = NULL;
	g->door_count = door_count;
	fill_door_cords(door, map);
	return (door);
}
