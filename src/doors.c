/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:53:52 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/06 15:56:57 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_door	*find_door(t_game *g, int y, int x)
{
	int	i;

	if (!g->door)
		return (NULL);
	i = 0;
	while (g->door[i])
	{
		if ((int)g->door[i]->pos_y == y && (int)g->door[i]->pos_x == x)
			return (g->door[i]);
		++i;
	}
	return (NULL);
}

int	get_door_side(char **map, int y, int x)
{
	if (y > 0 && map[y - 1] && map[y - 1][x] && is_wall(map[y - 1][x]))
	{
		if (map[y + 1] && map[y + 1][x] && is_wall(map[y + 1][x]))
			return (0);
	}
	return (1);
}

//----------------------------------------------

void	get_player_door_diff(t_player *player, t_door *door, int *diff_x, int *diff_y)
{
	int	player_x;
	int	player_y;
	int	door_x ;
	int	door_y;


	player_x = (int)player->pos_x;
	player_y = (int)player->pos_y;
	door_x = (int)door->pos_x;
	door_y = (int)door->pos_y;
	*diff_x = player_x - door_x;
	*diff_y = player_y - door_y;
}

int	check_adjacent(int diff_x, int diff_y)
{
	if ((diff_y == 0 && diff_x == 0)
		|| (diff_y == 1 && diff_x == 0)
		|| (diff_y == -1 && diff_x == 0)
		|| (diff_y == 0 && diff_x == 1)
		|| (diff_y == 0 && diff_x == -1))
		return (1);
    return (0);
}

int	is_player_adjacent_to_door(t_game *g, t_door *door)
{
	int	diff_x;
	int	diff_y;

	get_player_door_diff(g->player, door, &diff_x, &diff_y);
	return (check_adjacent(diff_x, diff_y));
}

int	update_single_door(t_game *g, t_door *door, double speed)
{
	double	old_pct;

	old_pct = door->open_pct;
	door->opening = is_player_adjacent_to_door(g, door);
	if (door->opening)
		door->open_pct += speed;
	else
		door->open_pct -= speed;

	if (door->open_pct < 0.0)
		door->open_pct = 0.0;
	if (door->open_pct > 1.0)
		door->open_pct = 1.0;

	if (fabs(door->open_pct - old_pct) > 0.0001)
    	return (1); // door mudou
    return (0); // door não mudou
}

int	update_doors(t_game *g)
{
	int		i;
	int		changed;
	double	speed;

	if (!g->door)
		return (0);

	changed = 0;
	speed = g->player->frame_time * 1.5;
	i = 0;
	while (g->door[i])
	{
		if (update_single_door(g, g->door[i], speed))
			changed = 1;
		i++;
	}
	return (changed);
}

int	hit_door_plane_x(t_ray *r, t_player *p, t_door *door)
{
	double	door_plane;
	double	hit_pos;
	double	local_pos;

	if (r->ray_dir_x == 0)
		return (0);

	door_plane = r->map_x + 0.5;
	r->perp_wall_dist = (door_plane - p->pos_x) / r->ray_dir_x;
	hit_pos = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
	local_pos = hit_pos - r->map_y;

	if (r->perp_wall_dist > 0 && local_pos >= 0.0
		&& local_pos <= (1.0 - door->open_pct))
	{
		r->wall_hit_pos_x = local_pos + door->open_pct;
		return (1);
	}
	return (0);
}

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
		return 0;

	r->door_side = get_door_side(g->map, r->map_y, r->map_x);

	if (r->door_side == 0)
		return hit_door_plane_x(r, p, door);
	else
		return hit_door_plane_y(r, p, door);
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