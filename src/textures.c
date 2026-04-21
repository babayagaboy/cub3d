/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:02:28 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/21 18:11:57 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void load_texture(t_mlx *mlx, t_texture **tex_d, char *path)
{
	*tex_d = malloc(sizeof(t_texture));
	if (!*tex_d)
		return ;
	(*tex_d)->img_ptr =  mlx_xpm_file_to_image(mlx->mlx, path, &(*tex_d)->width, &(*tex_d)->height);
	if (!(*tex_d)->img_ptr)
	{
		free(*tex_d);
		*tex_d = NULL;
		return ;
	}
	(*tex_d)->data = mlx_get_data_addr((*tex_d)->img_ptr, &(*tex_d)->bpp, &(*tex_d)->line_len, &(*tex_d)->endian);
	if (!(*tex_d)->data)
	{
		free(*tex_d);
		*tex_d = NULL;
		return ;
	}
}
int get_textures(t_mlx *mlx, t_ori_tex *tex)
{
	printf("NO: [%s]\n", tex->path_north);
	printf("SO: [%s]\n", tex->path_south);
	printf("WE: [%s]\n", tex->path_west);
	printf("EA: [%s]\n", tex->path_east);
	printf("F : [%s]\n", tex->path_floor);
	printf("C : [%s]\n", tex->path_ceiling);
	printf("D : [%s]\n", tex->path_door);
 
	tex->tex_north = NULL;
	tex->tex_south = NULL;
	tex->tex_east = NULL;
	tex->tex_west = NULL;
	tex->tex_floor = NULL;
	tex->tex_ceiling = NULL;
	tex->tex_door = NULL;

	load_texture(mlx, &tex->tex_north, tex->path_north);
	//printf("r = %d\n", r);
	load_texture(mlx, &tex->tex_south, tex->path_south);
	//printf("r = %d\n", r);
	load_texture(mlx, &tex->tex_east, tex->path_east);
	//printf("r = %d\n", r);
	load_texture(mlx, &tex->tex_west, tex->path_west);
	//printf("r = %d\n", r);
	if (tex->path_floor)
	{
		load_texture(mlx, &tex->tex_floor, tex->path_floor);
		printf("floor loaded\n");
	}
	//printf("r = %d\n");
	if (tex->path_ceiling)
	{
		load_texture(mlx, &tex->tex_ceiling, tex->path_ceiling);
		printf("ceiling loaded\n");
	}
	//printf("r = %d\n", r);
	load_texture(mlx, &tex->tex_door, tex->path_door);
	//printf("r = %d\n", r);
	if (!tex->tex_north || !tex->tex_south ||
		!tex->tex_east  || !tex->tex_west)
		return (0);
	return (1);
}