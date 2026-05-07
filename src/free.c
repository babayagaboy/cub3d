/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:43:27 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 20:23:06 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_mlx(t_mlx *m)
{
	mlx_mouse_show(m->mlx, m->win);
	if (m->mlx && m->img)
		mlx_destroy_image(m->mlx, m->img);
	if (m && m->win)
		mlx_destroy_window(m->mlx, m->win);
	if (m && m->mlx)
	{
		mlx_destroy_display(m->mlx);
		free(m->mlx);
		free(m);
		m = NULL;
	}
}

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
			free_t_texture(weapon->tex_arr[i], mlx, NULL);
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
			free_t_texture(weapon->tex_atk_arr[i], mlx, NULL);
			++i;
		}
		free(weapon->tex_atk_arr);
	}
}

void	free_texture_pack(t_game *g)
{
	free_t_texture(g->o_text->tex_north, g->mlx, g->o_text->path_north);
	free_t_texture(g->o_text->tex_south, g->mlx, g->o_text->path_south);
	free_t_texture(g->o_text->tex_east, g->mlx, g->o_text->path_east);
	free_t_texture(g->o_text->tex_west, g->mlx, g->o_text->path_west);
	free_t_texture(g->o_text->tex_floor, g->mlx, g->o_text->path_floor);
	free_t_texture(g->o_text->tex_ceiling, g->mlx, g->o_text->path_ceiling);
	free_t_texture(g->o_text->tex_door, g->mlx, g->o_text->path_door);
	free(g->o_text);
	free(g->txt);
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
	free_texture_pack(g);
	free_mlx(g->mlx);
	if (g->player)
		free(g->player);
	if (g->ray)
		free(g->ray);
	free_memory(g->elements_file);
	free_memory(g->map);
	fmi(g->buffer);
	free(g);
}
