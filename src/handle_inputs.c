/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:28:19 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 19:26:11 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	handle_movement(t_game *g)
{
	int	moved;

	moved = 0;
	if (move_forward(g))
		moved = 1;
	if (move_backward(g))
		moved = 1;
	if (move_right(g))
		moved = 1;
	if (move_left(g))
		moved = 1;
	return (moved);
}

int	handle_rotation_keys(t_game *g)
{
	int			moved;
	double		old_dir;
	double		old_plane;
	double		angle;
	t_player	*p;

	moved = 0;
	p = g->player;
	if (p->kp_ra || p->kp_la)
	{
		if (p->kp_ra)
			angle = p->rot_speed;
		else
			angle = -p->rot_speed;
		old_dir = p->dir_x;
		p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
		p->dir_y = old_dir * sin(angle) + p->dir_y * cos(angle);
		old_plane = p->plane_x;
		p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
		p->plane_y = old_plane * sin(angle) + p->plane_y * cos(angle);
		moved = 1;
	}
	return (moved);
}

int	handle_weapons(t_game *g)
{
	if (g->lightsaber->weapon_state != 0)
	{
		run_weapon_animation(g);
		return (1);
	}
	return (0);
}

int	key_press(int key, t_game *g)
{
	if (key == KEY_W)
		g->player->kp_w = 1;
	if (key == KEY_S)
		g->player->kp_s = 1;
	if (key == KEY_A)
		g->player->kp_a = 1;
	if (key == KEY_D)
		g->player->kp_d = 1;
	if (key == KEY_LEFT)
		g->player->kp_la = 1;
	if (key == KEY_RIGHT)
		g->player->kp_ra = 1;
	if (key == KEY_ESC)
	{
		free_project(g);
		exit(0);
		return (0);
	}
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == KEY_W)
		g->player->kp_w = 0;
	if (key == KEY_S)
		g->player->kp_s = 0;
	if (key == KEY_A)
		g->player->kp_a = 0;
	if (key == KEY_D)
		g->player->kp_d = 0;
	if (key == KEY_LEFT)
		g->player->kp_la = 0;
	if (key == KEY_RIGHT)
		g->player->kp_ra = 0;
	return (0);
}
