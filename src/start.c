/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:27:26 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 19:29:20 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	free_project(g);
	exit(0);
	return (0);
}

int	is_cub_path(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

int	handle_input(t_game *g)
{
	int	moved;
	int	redraw;
	int	door_changed;

	moved = 0;
	redraw = 0;
	get_time(g->player);
	if (handle_movement(g))
		moved = 1;
	if (handle_rotation_keys(g))
		moved = 1;
	if (handle_mouse_rotation(g))
		moved = 1;
	if (handle_weapons(g))
		redraw = 1;
	door_changed = update_doors(g);
	if (moved)
		upd_player_minimap(g);
	if (moved || door_changed || redraw)
		calc_rays(g->mlx, g->ray, g->player, g);
	return (0);
}

/* mlx_mouse_hide(game->mlx->mlx, game->mlx->win); */
void	start(t_game *game)
{
	game->minimap = copy_map(game->map, 0, game->map_h);
	game->map[(int)game->player->pos_y][(int)game->player->pos_x] = '0';
	game->player->prev_tile = '0';
	game->center_x = SCREENWIDTH / 2;
	game->center_y = SCREENHEIGHT / 2;
	game->mouse_dx = 0;
	game->warping = 0;
	game->player->kp_lc = 0;
	game->player->kp_rc = 0;
	game->door = NULL;
	game->door = get_door_coords(game, game->map);
	mlx_loop_hook(game->mlx->mlx, handle_input, game);
	get_guns_sprite(game);
	get_weapon_attack_sprite(game);
	calc_rays(game->mlx, game->ray, game->player, game);
	mlx_hook(game->mlx->win, 17, 0, close_window, game);
	mlx_hook(game->mlx->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(game->mlx->win, 5, 1L << 3, mouse_release, game);
	mlx_mouse_move(game->mlx->mlx, game->mlx->win,
		game->center_x, game->center_y);
}
