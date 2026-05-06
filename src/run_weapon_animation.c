/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_weapon_animation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 14:05:26 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:55:29 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	update_weapon_timer_and_frame(t_game *g)
{
	if (g->lightsaber->weapon_state == 0)
		return (0);
	g->lightsaber->weapon_anim_timer += g->player->frame_time;
	if (g->lightsaber->weapon_anim_timer < 0.066)
		return (0);
	g->lightsaber->weapon_anim_timer -= 0.066;
	if (g->lightsaber->weapon_state == 1 || g->lightsaber->weapon_state == 2)
		g->lightsaber->weapon_frame++;
	else if (g->lightsaber->weapon_state == 3)
		g->lightsaber->weapon_frame--;
	return (1);
}

void	handle_weapon_state_1(t_game *g)
{
	if (g->lightsaber->weapon_frame >= 6)
	{
		g->lightsaber->weapon_frame = 5;
		g->lightsaber->weapon_anim_timer = 0;
		g->lightsaber->deployed = 1;
		if (g->lightsaber->attack_pending)
		{
			g->lightsaber->attack_pending = 0;
			g->lightsaber->weapon_state = 2;
			g->lightsaber->weapon_frame = 1;
			g->lightsaber->weapon_anim_timer = 0;
		}
		else
			g->lightsaber->weapon_state = 0;
	}
}

void	handle_weapon_state_2(t_game *g)
{
	if (g->lightsaber->weapon_frame >= 6)
	{
		g->lightsaber->weapon_frame = 5;
		g->lightsaber->weapon_anim_timer = 0;
		g->lightsaber->weapon_state = 0;
	}
}

void	handle_weapon_state_3(t_game *g)
{
	if (g->lightsaber->weapon_frame <= 0)
	{
		g->lightsaber->weapon_frame = 0;
		g->lightsaber->weapon_anim_timer = 0;
		g->lightsaber->deployed = 0;
		g->lightsaber->weapon_state = 0;
	}
}

void	run_weapon_animation(t_game *g)
{
	if (!update_weapon_timer_and_frame(g))
		return ;
	if (g->lightsaber->weapon_state == 1)
		handle_weapon_state_1(g);
	else if (g->lightsaber->weapon_state == 2)
		handle_weapon_state_2(g);
	else if (g->lightsaber->weapon_state == 3)
		handle_weapon_state_3(g);
}
