/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:26:02 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 19:09:54 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return ;
	mlx->win = mlx_new_window(mlx->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	mlx->img = mlx_new_image(mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
			&mlx->line_len, &mlx->endian);
}

void	init_player(t_player *p)
{
	p->kp_w = 0;
	p->kp_s = 0;
	p->kp_a = 0;
	p->kp_d = 0;
	p->old_pos_x = p->pos_x;
	p->old_pos_y = p->pos_y;
	p->plane_y = p->dir_x * 0.66;
	p->plane_x = -p->dir_y * 0.66;
	p->time = get_timestamp();
	p->old_time = p->time;
	p->frame_time = 0;
	p->move_speed = 0;
	p->rot_speed = 0;
}

void	init_floor_ceil_params(t_ray *r, t_player *p, int i)
{
	int	pos;

	r->ray_dir_x_l = p->dir_x - p->plane_x;
	r->ray_dir_y_l = p->dir_y - p->plane_y;
	r->ray_dir_x_r = p->dir_x + p->plane_x;
	r->ray_dir_y_r = p->dir_y + p->plane_y;
	pos = i - (SCREENHEIGHT >> 1);
	p->pos_z = (SCREENHEIGHT >> 1);
	p->row_dis = p->pos_z / pos;
	r->floor_step_x = p->row_dis
		* (r->ray_dir_x_r - r->ray_dir_x_l) / SCREENWIDTH;
	r->floor_step_y = p->row_dis
		* (r->ray_dir_y_r - r->ray_dir_y_l) / SCREENWIDTH;
	r->floor_x = p->pos_x + p->row_dis * r->ray_dir_x_l;
	r->floor_y = p->pos_y + p->row_dis * r->ray_dir_y_l;
}
