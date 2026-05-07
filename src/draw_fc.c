/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:34:12 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 14:12:00 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_ceil_pixel(t_ori_tex *t, t_game *g, int screen_i, int j)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	*pixels;

	pixels = (int *)t->tex_ceiling->data;
	tex_x = (int)(t->tex_ceiling->width
			* (g->ray->floor_x - floor(g->ray->floor_x)));
	tex_y = (int)(t->tex_ceiling->height
			* (g->ray->floor_y - floor(g->ray->floor_y)));
	color = pixels[tex_y * (t->tex_ceiling->line_len / 4) + tex_x];
	g->buffer[SCREENHEIGHT - screen_i - 1][j] = color;
}

void	draw_floor_pixel(t_ori_tex *t, t_game *g, int screen_i, int j)
{
	int	tex_x;
	int	tex_y;
	int	color;
	int	*pixels;

	pixels = (int *)t->tex_floor->data;
	tex_x = (int)(t->tex_floor->width
			* (g->ray->floor_x - floor(g->ray->floor_x)));
	tex_y = (int)(t->tex_floor->height
			* (g->ray->floor_y - floor(g->ray->floor_y)));
	color = pixels[tex_y * (t->tex_floor->line_len / 4) + tex_x];
	g->buffer[screen_i][j] = color;
}

void	get_c_colored(t_ori_tex *tex, t_game *g)
{
	int	x;
	int	y;
	int	half_h;

	x = 0;
	half_h = SCREENHEIGHT >> 1;
	while (x < SCREENWIDTH)
	{
		y = 0;
		while (y < half_h)
		{
			if (g->buffer[y][x] == 0)
				g->buffer[y][x] = get_color(tex->rgb_ceiling[0],
						tex->rgb_ceiling[1], tex->rgb_ceiling[2]);
			++y;
		}
		++x;
	}
}

void	get_f_colored(t_ori_tex *tex, t_game *g)
{
	int	x;
	int	y;
	int	half_h;

	x = 0;
	half_h = SCREENHEIGHT >> 1;
	while (x < SCREENWIDTH)
	{
		y = half_h;
		while (y < SCREENHEIGHT)
		{
			if (g->buffer[y][x] == 0)
				g->buffer[y][x] = get_color(tex->rgb_floor[0],
						tex->rgb_floor[1], tex->rgb_floor[2]);
			++y;
		}
		++x;
	}
}

void	draw_floor_ceiling(t_game *g, t_player *player, t_ori_tex *tex)
{
	int	i;

	i = 0;
	while (i < SCREENHEIGHT)
	{
		get_fc(g, player, tex, i);
		++i;
	}
}
