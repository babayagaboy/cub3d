/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:18:21 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 14:12:00 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREENWIDTH || y < 0 || y >= SCREENHEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	drawbuffer(t_mlx *mlx, t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			put_pixel(mlx, x, y, g->buffer[y][x]);
			++x;
		}
		++y;
	}
}

void	put_square(int y, int x, int color, t_game *g)
{
	int	i;
	int	j;

	i = y * g->sp;
	while (i < y * g->sp + g->sp)
	{
		j = x * g->sp;
		while (j < x * g->sp + g->sp)
		{
			put_pixel(g->mlx, j, i, color);
			++j;
		}
		++i;
	}
}

void	draw_vertical_line(t_draw_params *dp, t_game *g)
{
	int	start;
	int	tex_y;
	int	*pixels;
	int	color;

	start = dp->draw_start;
	while (start <= dp->draw_end)
	{
		if (start >= 0 && start < SCREENHEIGHT
			&& dp->i >= 0 && dp->i < SCREENWIDTH)
		{
			tex_y = (int)dp->r->tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= dp->t->height)
				tex_y = dp->t->height - 1;
			pixels = (int *)dp->t->data;
			color = pixels[tex_y * (dp->t->line_len / 4) + dp->tex_x];
			g->buffer[start][dp->i] = color;
		}
		dp->r->tex_pos += dp->r->tex_step;
		++start;
	}
}

void	clear_buffer(t_game *g)
{
	int	i;
	int	x;

	i = 0;
	while (i < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			g->buffer[i][x] = 0;
			++x;
		}
		++i;
	}
}
