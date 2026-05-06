/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:53:52 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:10:28 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_door_side(char **map, int y, int x)
{
	if (y > 0 && map[y - 1] && map[y - 1][x] && is_wall(map[y - 1][x]))
	{
		if (map[y + 1] && map[y + 1][x] && is_wall(map[y + 1][x]))
			return (0);
	}
	return (1);
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
