/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:07:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 00:52:38 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	init_buffer(t_game *g)
{
	int	i;

	i = 0;
	while (i < screenHeight)
	{
		g->buffer[i] = malloc(sizeof(int) * screenWidth);
		if (!g->buffer[i])
		{
			while (--i)
			{
				free(g->buffer[i]);
			}
			free(g->buffer);
			return (0);
		}
		++i;
	}
	return (1);
}

int	malloc_structs(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (1);
	(*game)->player = malloc(sizeof(t_player));
	if (!(*game)->player)
		return (free(*game), 1);
	(*game)->mlx = malloc(sizeof(t_mlx));
	if (!(*game)->mlx)
		return (free((*game)->player), free(*game), 1);
	(*game)->o_text = malloc(sizeof(t_ori_tex));
	if (!(*game)->o_text)
		return (free((*game)->mlx), free((*game)->player), free(*game), 1);
	(*game)->txt = malloc(sizeof(t_texture));
	if (!(*game)->txt)
		return (free((*game)->o_text), free((*game)->mlx),
			free((*game)->player), free(*game), 1);
	(*game)->buffer = malloc(sizeof(int *) * screenHeight);
	if (!(*game)->buffer)
		return (free((*game)->player), free((*game)->txt), free(*game), 1);
	if (!init_buffer(*game))
		return (free((*game)->player), free((*game)->txt), free(*game), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (malloc_structs(&game))
		return (-1);
	init_mlx(game->mlx);
	if (!game->mlx->mlx || !game->mlx->win
		|| !game->mlx->img || !game->mlx->addr)
		return (free(game->mlx), 1);
	init_player(game->player);
	if (!parser(argc, argv, game))
		return (free(game->player), free(game->mlx), free(game), 0);
	init_player(game->player);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return (free(game->mlx), free(game->player), 1);
	game->player->kp_ra = 0;
	game->player->kp_la = 0;
	start(game);
	mlx_loop(game->mlx->mlx);
	return (0);
}
