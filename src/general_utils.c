/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:42:11 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 19:25:31 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_xpm_path(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

void	run_dda(t_ray *r, t_player *p, t_game *g)
{
	r->hit = 0;
	while (r->hit == 0)
		step_dda(r, p, g);
	calc_perp_wall_dist(r);
}

void	calc_camera(t_ray *r, t_player *p, int i)
{
	r->camera_x = 2 * i / (double)SCREENWIDTH - 1;
	r->ray_dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->ray_dir_x = p->dir_x + p->plane_x * r->camera_x;
}

void	upd_player_minimap(t_game *g)
{
	g->minimap[(int)g->player->old_pos_y][(int)g->player->old_pos_x]
		= g->player->prev_tile;
	g->player->prev_tile
		= g->minimap[(int)g->player->pos_y][(int)g->player->pos_x];
	g->minimap[(int)g->player->pos_y][(int)g->player->pos_x]
		= get_player_marker(g->player);
	g->player->old_pos_y = g->player->pos_y;
	g->player->old_pos_x = g->player->pos_x;
}

void	clear_img_buffer(t_mlx *mlx)
{
	int	i;
	int	size;

	i = 0;
	size = mlx->line_len * SCREENHEIGHT;
	while (i < size)
	{
		mlx->addr[i] = 0;
		++i;
	}
}
