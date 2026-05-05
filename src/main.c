/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:07:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/05 23:39:00 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	game->door =  malloc(sizeof(t_door *));
	if (!game->door)
		return (1);
	init_mlx(game->mlx);
	if (!game->mlx->mlx || !game->mlx->win || !game->mlx->img || !game->mlx->addr)
		return (free(game->mlx), 1);
	init_player(game->player);
	if(!parser(argc, argv, game))
		return (free(game->player), free(game->mlx) ,free(game), 0);
	init_player(game->player);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return (free(game->mlx), free(game->player), 1);
	game->player->kp_ra = 0;
	game->player->kp_la = 0;
	start(game);
	mlx_loop(game->mlx->mlx);
	for (int i = 0; i < game->door_count; i++)
		free(game->door[i]);
	free(game->door);
	free(game->mlx);
	free(game->player);
	free(game->ray);
	free(game->player);
	free(game->txt);
	free(game->o_text);
	free_memory(game->elements_file);
	free_memory(game->map);
	free (game);
	return (0);
}
