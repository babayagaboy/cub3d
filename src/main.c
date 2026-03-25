/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:07:06 by hgutterr          #+#    #+#             */
/*   Updated: 2026/03/25 15:01:12 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    init_player(t_player *p)
{
	//p->pos_y = 12;  //x and y start position //get_player_coords()
	//p->pos_x = 22;

	//p->dir_y = 0;	//initial direction vector (N, S, W, E)
	//p->dir_x = -1;

	//^^ mykyta ^^

	p->plane_y = p->dir_x * 0.66; //the 2d raycaster version of camera plane
	p->plane_x = -p->dir_y * 0.66;
	
	p->time = 0; //time of current frame
	p->old_time = 0; //time of previous frame
	p->frame_time = 0;

	p->move_speed = 0;
	p->rot_speed = 0;
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
		return (free(game->player), 0);
	printf("player coords = y: %f, x: %f\n", game->player->pos_y, game->player->pos_x);
	printf("player orientation = dir_y: %f, dir_x: %f\n", game->player->dir_y, game->player->dir_x);
	/*game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (1);
	init_mlx(game->mlx);
	if (!game->mlx->mlx || !game->mlx->win || !game->mlx->img || !game->mlx->addr)
		return (free(game->mlx), free(game->player), 1);
	game->ray = malloc(sizeof(t_ray));
	if (!game->ray)
		return (free(game->mlx), free(game->player), 1);
	printf("BEFORE START\n");
	start(game);
	printf("AFTER START\n");
	mlx_loop(game->mlx->mlx);
	free(game);
	free(game->mlx);
	free(game->player);
	free(game->ray);*/
	free_memory(game->elements_file);
	free_memory(game->map);
	return (0);
}
