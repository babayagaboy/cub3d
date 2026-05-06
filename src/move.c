/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:31:01 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:54:07 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	move_forward(t_game *g)
{
	t_player	*p;

	p = g->player;
	if (!p->kp_w)
		return (0);
	if (is_walkable_tile(g, (int)p->pos_y,
			(int)(p->pos_x + p->dir_x * p->move_speed)))
		p->pos_x += p->dir_x * p->move_speed;
	if (is_walkable_tile(g,
			(int)(p->pos_y + p->dir_y * p->move_speed), (int)p->pos_x))
		p->pos_y += p->dir_y * p->move_speed;
	return (1);
}

int	move_backward(t_game *g)
{
	t_player	*p;

	p = g->player;
	if (!p->kp_s)
		return (0);
	if (is_walkable_tile(g, (int)p->pos_y,
			(int)(p->pos_x - p->dir_x * p->move_speed)))
		p->pos_x -= p->dir_x * p->move_speed;
	if (is_walkable_tile(g,
			(int)(p->pos_y - p->dir_y * p->move_speed), (int)p->pos_x))
		p->pos_y -= p->dir_y * p->move_speed;
	return (1);
}

int	move_right(t_game *g)
{
	t_player	*p;

	p = g->player;
	if (!p->kp_d)
		return (0);
	if (is_walkable_tile(g,
			(int)(p->pos_y + p->dir_x * p->move_speed), (int)p->pos_x))
		p->pos_y += p->dir_x * p->move_speed;
	if (is_walkable_tile(g,
			(int)p->pos_y, (int)(p->pos_x - p->dir_y * p->move_speed)))
		p->pos_x -= p->dir_y * p->move_speed;
	return (1);
}

int	move_left(t_game *g)
{
	t_player	*p;

	p = g->player;
	if (!p->kp_a)
		return (0);
	if (is_walkable_tile(g,
			(int)(p->pos_y - p->dir_x * p->move_speed), (int)p->pos_x))
		p->pos_y -= p->dir_x * p->move_speed;
	if (is_walkable_tile(g,
			(int)p->pos_y, (int)(p->pos_x + p->dir_y * p->move_speed)))
		p->pos_x += p->dir_y * p->move_speed;
	return (1);
}
