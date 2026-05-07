/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:39:21 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 14:12:00 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	calc_draw_positions(t_ray *r, int *draw_start, int *draw_end)
{
	int	line_height;

	if (r->perp_wall_dist <= 0)
		r->perp_wall_dist = 0.1;
	line_height = (int)(SCREENHEIGHT / r->perp_wall_dist);
	*draw_start = ((-1 * line_height) >> 1) + (SCREENHEIGHT >> 1);
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = (line_height >> 1) + (SCREENHEIGHT >> 1);
	if (*draw_end >= SCREENHEIGHT)
		*draw_end = SCREENHEIGHT - 1;
	return (line_height);
}

void	calc_wall_hit(t_ray *r, t_player *p)
{
	if (r->hit != 2 && r->side == 0)
		r->wall_hit_pos_x = p->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else if (r->hit != 2)
		r->wall_hit_pos_x = p->pos_x + r->perp_wall_dist * r->ray_dir_x;
}

void	get_walls(t_game *g, t_player *p, t_ori_tex *tex, int i)
{
	t_texture		*t;
	t_draw_params	dp;
	int				tex_x;
	t_wall_calc		wc;

	wc.line_height = calc_draw_positions(g->ray, &wc.draw_start, &wc.draw_end);
	calc_wall_hit(g->ray, p);
	t = select_texture(g->ray, tex);
	tex_x = calc_tex_mapping(g->ray, t, wc.line_height, wc.draw_start);
	dp = (t_draw_params){g->ray, t, tex_x, wc.draw_start, wc.draw_end, i};
	draw_vertical_line(&dp, g);
}

void	cast_rays(t_ray *ray, t_player *player, t_ori_tex *tex, t_game *g)
{
	int	i;

	i = 0;
	while (i < SCREENWIDTH)
	{
		calc_camera(ray, player, i);
		calc_dda(ray, player);
		run_dda(ray, player, g);
		get_walls(g, player, tex, i);
		++i;
	}
}

void	calc_rays(t_mlx *mlx, t_ray *ray, t_player *player, t_game *g)
{
	clear_img_buffer(mlx);
	draw_floor_ceiling(g, player, g->o_text);
	cast_rays(ray, player, g->o_text, g);
	handle_hud(g);
	drawbuffer(g->mlx, g);
	clear_buffer(g);
	minimap(g);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
