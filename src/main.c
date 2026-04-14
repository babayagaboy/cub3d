/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:07:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/14 16:19:06 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void dubg(t_game *game)
{
	printf("player coords = y: %f, x: %f\n", game->player->pos_y, game->player->pos_x);
	printf("player orientation = dir_y: %f, dir_x: %f\n", game->player->dir_y, game->player->dir_x);
	printf("map coords = y: %i, x: %d\n", game->map_h, game->map_w);

}

int	main(int argc, char **argv)
{
	t_game *game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		return (free(game), 1);
	init_player(game->player);
	if(!parser(argc, argv, game))
		return (free(game->player), free(game), 0);
	init_player(game->player);
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (1);
	init_mlx(game->mlx);
	if (!game->mlx->mlx || !game->mlx->win || !game->mlx->img || !game->mlx->addr)
		return (free(game->mlx), free(game->player), 1);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return (free(game->mlx), free(game->player), 1);
	dubg(game);
	start(game);
	mlx_loop(game->mlx->mlx);
	free(game);
	free(game->mlx);
	free(game->player);
	free(game->ray);
	free(game->player);
	free_memory(game->elements_file);
	free_memory(game->map);
	free (game);
	return (0);
}
