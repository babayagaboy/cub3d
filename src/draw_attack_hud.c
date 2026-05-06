/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_attack_hud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:04:34 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:14:10 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_attack_hud_start_pos(t_texture *tex, float scale,
		int *start_x, int *start_y)
{
	*start_x = (screenWidth - (tex->width / scale)) + (screenWidth / 18);
	*start_y = screenHeight - (tex->height / scale) + 50;
}

void	draw_attack_hud_row(t_attack_hud *hud, t_game *g, int y)
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

void	draw_attack_hud_pixels(t_attack_hud *hud, t_game *g)
{
	int	y;

	y = 0;
	while (y < hud->tex->height)
	{
		draw_attack_hud_row(hud, g, y);
		y++;
	}
}

void	draw_attack_hud(t_game *g, int i)
{
	t_attack_hud	hud;

	if (!g->lightsaber || !g->lightsaber->tex_atk_arr[i])
		return ;
	hud.tex = g->lightsaber->tex_atk_arr[i];
	hud.scale = 1.5;
	get_attack_hud_start_pos(hud.tex, hud.scale, &hud.start_x, &hud.start_y);
	draw_attack_hud_pixels(&hud, g);
}
