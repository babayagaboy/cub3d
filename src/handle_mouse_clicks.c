/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_clicks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:38:07 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:45:19 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	handle_left_click(t_game *g)
{
	if (g->lightsaber->weapon_state != 0)
		return ;
	g->player->kp_lc = 1;
	if (g->lightsaber->deployed == 0 || g->lightsaber->weapon_state == 1)
		return ;
	g->lightsaber->weapon_state = 2;
	g->lightsaber->weapon_frame = 1;
	g->lightsaber->deployed = 1;
}

void	handle_right_click(t_game *g)
{
	if (g->lightsaber->weapon_state != 0)
		return ;
	g->player->kp_rc = 1;
	if (g->lightsaber->deployed == 0)
	{
		g->lightsaber->weapon_state = 1;
		g->lightsaber->weapon_anim_timer = 0;
		g->lightsaber->deployed = 1;
	}
	else
	{
		g->lightsaber->weapon_state = 3;
		g->lightsaber->weapon_frame = 5;
		g->lightsaber->weapon_anim_timer = 0;
	}
}
