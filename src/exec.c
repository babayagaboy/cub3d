/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:07:28 by hgutterr          #+#    #+#             */
/*   Updated: 2026/03/16 20:07:28 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3d");
	mlx->img = mlx_new_image(mlx, 800, 600);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
}

int	main(void)
{
	t_mlx	*mlx;
	mlx = malloc(sizeof(t_mlx));
	init_mlx(mlx);
	put_pixel(mlx, 100, 100, 0xFF0000);
	free(mlx);
}