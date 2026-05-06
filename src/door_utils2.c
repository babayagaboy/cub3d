/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:00:17 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 00:00:17 by hgutterr         ###   ########.fr       */
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

void	get_player_door_diff(t_player *player, t_door *door,
		int *diff_x, int *diff_y)
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
		return (1);
	return (0);
}
