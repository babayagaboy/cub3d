/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:29:30 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:46:24 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	handle_mouse_rotation(t_game *g)
{
	if (g->mouse_dx != 0)
	{
		apply_mouse_rotation(g);
		return (1);
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	(void)y;
	if (g->warping)
	{
		g->warping = 0;
		return (0);
	}
	g->mouse_dx += x - g->center_x;
	g->warping = 1;
	mlx_mouse_move(g->mlx->mlx, g->mlx->win, g->center_x, g->center_y);
	return (0);
}

void	apply_mouse_rotation(t_game *g)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	if (g->mouse_dx == 0)
		return ;
	rot = g->mouse_dx * 0.002;
	old_dir_x = g->player->dir_x;
	g->player->dir_x = g->player->dir_x * cos(rot)
		- g->player->dir_y * sin(rot);
	g->player->dir_y = old_dir_x * sin(rot)
		+ g->player->dir_y * cos(rot);
	old_plane_x = g->player->plane_x;
	g->player->plane_x = g->player->plane_x * cos(rot)
		- g->player->plane_y * sin(rot);
	g->player->plane_y = old_plane_x * sin(rot)
		+ g->player->plane_y * cos(rot);
	g->mouse_dx = 0;
}

int	mouse_press(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == 1)
		handle_left_click(g);
	else if (button == 3)
		handle_right_click(g);
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == 1)
		g->player->kp_lc = 0;
	if (button == 3)
		g->player->kp_rc = 0;
	return (0);
}
