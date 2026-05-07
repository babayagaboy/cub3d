/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:02:28 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 20:33:28 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	calc_tex_mapping(t_ray *r, t_texture *t, int line_height, int draw_start)
{
	int	tex_x;

	r->wall_hit_pos_x -= floor(r->wall_hit_pos_x);
	r->tex_step = 1.0 * t->height / line_height;
	r->tex_pos = (draw_start - (SCREENHEIGHT >> 1)
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

int	load_texture(t_mlx *mlx, t_texture **tex_d, char *path)
{
	*tex_d = NULL;
	*tex_d = malloc(sizeof(t_texture));
	if (!*tex_d)
		return (1);
	(*tex_d)->img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &(*tex_d)->width,
			&(*tex_d)->height);
	if (!(*tex_d)->img_ptr)
	{
		free(*tex_d);
		free(path);
		*tex_d = NULL;
		return (1);
	}
	(*tex_d)->data = mlx_get_data_addr((*tex_d)->img_ptr, &(*tex_d)->bpp,
			&(*tex_d)->line_len, &(*tex_d)->endian);
	if (!(*tex_d)->data)
	{
		free(*tex_d);
		free(path);
		*tex_d = NULL;
		return (1);
	}
	return (0);
}

int	get_textures(t_mlx *mlx, t_ori_tex *tex)
{
	int	i;

	i = 0;
	if (tex->path_north)
		i += load_texture(mlx, &tex->tex_north, tex->path_north);
	if (tex->path_south)
		i += load_texture(mlx, &tex->tex_south, tex->path_south);
	if (tex->path_east)
		i += load_texture(mlx, &tex->tex_east, tex->path_east);
	if (tex->path_west)
		i += load_texture(mlx, &tex->tex_west, tex->path_west);
	if (tex->path_floor)
		i += load_texture(mlx, &tex->tex_floor, tex->path_floor);
	if (tex->path_ceiling)
		i += load_texture(mlx, &tex->tex_ceiling, tex->path_ceiling);
	if (tex->path_door)
		i += load_texture(mlx, &tex->tex_door, tex->path_door);
	if (i)
	{
		printf("Error\nLoading texture file\n");
		return (0);
	}
	return (1);
}
