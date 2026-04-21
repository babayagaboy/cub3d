/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:02:28 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/15 17:42:37 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int load_texture(t_mlx *mlx, t_texture **tex_d, char *path)
{
    *tex_d = malloc(sizeof(t_texture));
    if (!*tex_d)
        return (0);

    (*tex_d)->img_ptr = mlx_xpm_file_to_image(mlx->mlx, path, &(*tex_d)->width, &(*tex_d)->height);
    if (!(*tex_d)->img_ptr)
        return (0);

    (*tex_d)->data = mlx_get_data_addr((*tex_d)->img_ptr, &(*tex_d)->bpp, &(*tex_d)->line_len, &(*tex_d)->endian);

    return (1);
}
int get_textures(t_mlx *mlx, t_ori_tex *tex)
{
    int r;

    /*printf("NO: [%s]\n", tex->path_north);
    printf("SO: [%s]\n", tex->path_south);
    printf("WE: [%s]\n", tex->path_west);
    printf("EA: [%s]\n", tex->path_east);
    printf("F : [%s]\n", tex->path_floor);
    printf("C : [%s]\n", tex->path_ceiling);
    printf("D : [%s]\n", tex->path_door);*/
 
    r = 0;
    r += load_texture(mlx, &tex->tex_north, tex->path_north);
    //printf("r = %d\n", r);
    r += load_texture(mlx, &tex->tex_south, tex->path_south);
    //printf("r = %d\n", r);
    r += load_texture(mlx, &tex->tex_east, tex->path_east);
    //printf("r = %d\n", r);
    r += load_texture(mlx, &tex->tex_west, tex->path_west);
    //printf("r = %d\n", r);
    if (tex->path_floor)
        r += load_texture(mlx, &tex->tex_floor, tex->path_floor);
    //printf("r = %d\n", r);
    if (tex->path_ceiling)
        r += load_texture(mlx, &tex->tex_ceiling, tex->path_ceiling);
    //printf("r = %d\n", r);
    r += load_texture(mlx, &tex->tex_door, tex->path_door);
    //printf("r = %d\n", r);
    if (r == 7 || r == 5)
        return (1);
    return (0);
}