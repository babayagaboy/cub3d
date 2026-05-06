/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:39:40 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/06 16:25:29 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	calc_cell_size(t_game *g)
{
	if (g->map_h > g->map_w)
		return ((int)(300 / g->map_h));
	else
		return ((int)(300 / g->map_w));
}

void	draw_cell(t_game *g, int i, int j)
{
	char	c;

	c = g->minimap[i][j];
	if (is_wall(c))
		put_square(i, j, 0x48494B, g);
	if (c == '0')
		put_square(i, j, 0x808588, g);
	if (c == 'D')
		put_square(i, j, 0x0000FF, g);
	if (is_player(c))
		put_square(i, j, 0xFF0000, g);
}

void	draw_minimap_row(t_game *g, int i)
{
	int	j;

	j = 0;
	while (g->minimap[i][j])
	{
		draw_cell(g, i, j);
		++j;
	}
}

char	get_player_marker(t_player *player)
{
	if (fabs(player->dir_x) >= fabs(player->dir_y))
	{
		if (player->dir_x >= 0)
			return ('E');
		return ('W');
	}
	if (player->dir_y >= 0)
		return ('S');
	return ('N');
}

void	minimap(t_game *g)
{
	int	i;

	i = 0;
	g->sp = calc_cell_size(g);
	while (g->minimap[i])
	{
		draw_minimap_row(g, i);
		++i;
	}
}
