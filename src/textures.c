/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:02:28 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 00:56:39 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	calc_tex_mapping(t_ray *r, t_texture *t, int line_height, int draw_start)
{
	int	tex_x;

	r->wall_hit_pos_x -= floor(r->wall_hit_pos_x);
	r->tex_step = 1.0 * t->height / line_height;
	r->tex_pos = (draw_start - (screenHeight >> 1)
			+ (line_height >> 1)) * r->tex_step;
	tex_x = (int)(r->wall_hit_pos_x * (1.0 * t->width));
	if (r->side == 0 && r->ray_dir_x > 0)
		tex_x = t->width - tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tex_x = t->width - tex_x - 1;
	return (tex_x);
}

t_texture	*select_texture(t_ray *r, t_ori_tex *tex)
{
	if (r->hit == 2)
		return (tex->tex_door);
	else if (r->side == 0 && r->ray_dir_x > 0)
		return (tex->tex_west);
	else if (r->side == 0)
		return (tex->tex_east);
	else if (r->ray_dir_y > 0)
		return (tex->tex_north);
	else
		return (tex->tex_south);
}

void	load_texture(t_mlx *mlx, t_texture **tex_d, char *path)
{
	*tex_d = malloc(sizeof(t_texture));
	if (!*tex_d)
		return ;
	(*tex_d)->img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &(*tex_d)->width,
			&(*tex_d)->height);
	if (!(*tex_d)->img_ptr)
	{
		free(*tex_d);
		*tex_d = NULL;
		return ;
	}
	(*tex_d)->data = mlx_get_data_addr((*tex_d)->img_ptr, &(*tex_d)->bpp,
			&(*tex_d)->line_len, &(*tex_d)->endian);
	if (!(*tex_d)->data)
	{
		free(*tex_d);
		*tex_d = NULL;
		return ;
	}
}

int	get_textures(t_mlx *mlx, t_ori_tex *tex)
{
	tex->tex_north = NULL;
	tex->tex_south = NULL;
	tex->tex_east = NULL;
	tex->tex_west = NULL;
	tex->tex_floor = NULL;
	tex->tex_ceiling = NULL;
	tex->tex_door = NULL;
	load_texture(mlx, &tex->tex_north, tex->path_north);
	load_texture(mlx, &tex->tex_south, tex->path_south);
	load_texture(mlx, &tex->tex_east, tex->path_east);
	load_texture(mlx, &tex->tex_west, tex->path_west);
	if (tex->path_floor)
		load_texture(mlx, &tex->tex_floor, tex->path_floor);
	if (tex->path_ceiling)
		load_texture(mlx, &tex->tex_ceiling, tex->path_ceiling);
	load_texture(mlx, &tex->tex_door, tex->path_door);
	if (!tex->tex_north || !tex->tex_south
		|| !tex->tex_east || !tex->tex_west)
		return (0);
	return (1);
}
