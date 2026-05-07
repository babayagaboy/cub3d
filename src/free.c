/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:43:27 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 16:51:31 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_weapon(t_weapon *weapon, t_mlx *mlx)
{
	int	i;

	if (!weapon)
		return ;
	if (weapon->tex_arr)
	{
		i = 0;
		while (weapon->tex_arr[i])
		{
			free_t_texture(weapon->tex_arr[i], mlx);
			++i;
		}
		free(weapon->tex_arr);
	}
}

void	free_weapon_attk(t_weapon *weapon, t_mlx *mlx)
{
	int	i;

	if (!weapon)
		return ;
	if (weapon->tex_atk_arr)
	{
		i = 0;
		while (weapon->tex_atk_arr[i])
		{
			free_t_texture(weapon->tex_atk_arr[i], mlx);
			++i;
		}
		free(weapon->tex_atk_arr);
	}
}

void	free_texture_pack(t_game *g)
{
	free_t_texture(g->o_text->tex_north, g->mlx);
	free_t_texture(g->o_text->tex_south, g->mlx);
	free_t_texture(g->o_text->tex_east, g->mlx);
	free_t_texture(g->o_text->tex_west, g->mlx);
	free_t_texture(g->o_text->tex_floor, g->mlx);
	free_t_texture(g->o_text->tex_ceiling, g->mlx);
	free_t_texture(g->o_text->tex_door, g->mlx);
	free(g->o_text->path_floor);
	free(g->o_text->path_ceiling);
	free(g->o_text->path_door);
	free(g->o_text->path_north);
	free(g->o_text->path_south);
	free(g->o_text->path_west);
	free(g->o_text->path_east);
	free(g->o_text);
	free(g->txt);
	if (g->mlx && g->mlx->mlx)
	{
		mlx_destroy_display(g->mlx->mlx);
		free(g->mlx);
		g->mlx = NULL;
	}
}

void	free_project(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->door_count)
		free(g->door[i++]);
	free(g->door);
	if (g->lightsaber)
	{
		free_weapon(g->lightsaber, g->mlx);
		free_weapon_attk(g->lightsaber, g->mlx);
		free(g->lightsaber);
	}
	free_memory(g->minimap);
	if (g->mlx && g->mlx->img)
		mlx_destroy_image(g->mlx->mlx, g->mlx->img);
	if (g->mlx && g->mlx->win)
	{
		mlx_mouse_show(g->mlx->mlx, g->mlx->win);
		mlx_destroy_window(g->mlx->mlx, g->mlx->win);
	}
	free_texture_pack(g);
	free(g->player);
	free(g->ray);
	free_memory(g->elements_file);
	free_memory(g->map);
	free_memory_int(g->buffer);
	free(g);
}
