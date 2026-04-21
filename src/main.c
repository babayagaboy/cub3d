/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:07:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/04/21 17:35:05 by hgutterr         ###   ########.fr       */
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
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (1);
	game->o_text = malloc(sizeof(t_ori_tex));
	if (!game->o_text)
		return (1);
	game->txt = malloc(sizeof(t_texture));
	if (!game->txt)
		return (1);
	init_mlx(game->mlx);
	if (!game->mlx->mlx || !game->mlx->win || !game->mlx->img || !game->mlx->addr)
		return (free(game->mlx), 1);
	init_player(game->player);
	if(!parser(argc, argv, game))
		return (free(game->player), free(game->mlx) ,free(game), 0);

	// for (int i = 0; i < 3; ++i)
	// 	printf("In main rbg_ceiling[%d]: %d\n", i, game->o_text->rgb_ceiling[i]);
	// printf("\n");
	// for (int i = 0; i < 3; ++i)
	// 	printf("In main rbg_floor[%d]: %d\n", i, game->o_text->rgb_floor[i]);
		
	init_player(game->player);
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
