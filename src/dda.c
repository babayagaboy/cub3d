/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:45:36 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/06 23:57:07 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	calc_dda_axis_x(t_ray *r, t_player *p)
{
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
}

void	calc_dda_axis_y(t_ray *r, t_player *p)
{
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

void	calc_dda(t_ray *r, t_player *p)
{
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	calc_dda_axis_x(r, p);
	calc_dda_axis_y(r, p);
}

void	step_dda(t_ray *r, t_player *p, t_game *g)
{
	if (r->side_dist_x < r->side_dist_y)
	{
		r->side_dist_x += r->delta_dist_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_dist_y += r->delta_dist_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
	if (g->map[r->map_y][r->map_x] == 'D')
	{
		if (hit_door_plane(r, p, g))
		{
			r->hit = 2;
			r->side = r->door_side;
		}
	}
	else if (g->map[r->map_y][r->map_x] != '0')
		r->hit = 1;
}

void	calc_perp_wall_dist(t_ray *r)
{
	if (r->hit == 2)
		return ;
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}
