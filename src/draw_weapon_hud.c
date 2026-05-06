/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon_hud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:04:34 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/06 17:30:35 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_weapon_hud_start_pos(t_texture *tex, float scale, int *start_x, int *start_y)
{
	*start_x = (screenWidth - (tex->width / scale)) + (screenWidth / 18);
	*start_y = screenHeight - (tex->height / scale) + 50;
}

void	draw_weapon_hud_row(t_weapon_hud *hud, t_game *g, int y)
{
	int				x;
	unsigned int	color;
	unsigned int	*pixels;
	int				bx;
	int				by;

	x = 0;
	pixels = (unsigned int *)hud->tex->data;
	while (x < hud->tex->width)
	{
		bx = hud->start_x + (x / hud->scale);
		by = hud->start_y + (y / hud->scale);

		color = pixels[y * (hud->tex->line_len / 4) + x];
		if (bx >= 0 && bx < screenWidth && by >= 0 && by < screenHeight
			&& (color & 0xFF000000) == 0)
		{
			g->buffer[by][bx] = color;
		}
		x++;
	}
}

void	draw_weapon_hud_pixels(t_weapon_hud *hud, t_game *g)
{
	int	y;

	y = 0;
	while (y < hud->tex->height)
	{
		draw_weapon_hud_row(hud, g, y);
		y++;
	}
}

void	draw_weapon_hud(t_game *g, int i)
{
	t_weapon_hud	hud;

	if (!g->lightsaber || !g->lightsaber->tex_arr[i])
		return ;

	hud.tex = g->lightsaber->tex_arr[i];
	hud.scale = 1.5;

	get_weapon_hud_start_pos(hud.tex, hud.scale, &hud.start_x, &hud.start_y);
	draw_weapon_hud_pixels(&hud, g);
}

void	handle_hud(t_game *g)
{
	if (!g->o_text->path_ceiling)
		get_c_colored(g->o_text, g);
	if (!g->o_text->path_floor)
		get_f_colored(g->o_text, g);

	if (g->lightsaber->weapon_state == 2)
		draw_attack_hud(g, g->lightsaber->weapon_frame);
	else
		draw_weapon_hud(g, g->lightsaber->weapon_frame);
}
