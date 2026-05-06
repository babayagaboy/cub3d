/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attack_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:04:34 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:24:39 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_lightsaber_attack_texture_path(int i)
{
	if (i == 0)
		return ("./assets/SwordAttack1.xpm");
	else if (i == 1)
		return ("./assets/SwordAttack2.xpm");
	else if (i == 2)
		return ("./assets/SwordAttack3.xpm");
	else if (i == 3)
		return ("./assets/SwordAttack4.xpm");
	else if (i == 4)
		return ("./assets/SwordAttack5.xpm");
	else
		return ("./assets/SwordAttack6.xpm");
}

int	init_lightsaber_attack_struct(t_game *g)
{
	g->lightsaber->tex_atk_arr = ft_calloc(7, sizeof(t_texture *));
	if (!g->lightsaber->tex_atk_arr)
	{
		free_weapon(g->lightsaber, g->mlx);
		free(g->lightsaber);
		return (1);
	}
	g->lightsaber->weapon_frame = 0;
	g->lightsaber->weapon_anim_timer = 0.0;
	g->lightsaber->weapon_state = 0;
	g->lightsaber->attack_pending = 0;
	g->lightsaber->deployed = 0;
	return (0);
}

int	load_lightsaber_attack_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		load_texture(g->mlx, &g->lightsaber->tex_atk_arr[i],
			get_lightsaber_attack_texture_path(i));
		if (!g->lightsaber->tex_atk_arr[i])
		{
			free_weapon(g->lightsaber, g->mlx);
			free_weapon_attk(g->lightsaber, g->mlx);
			free(g->lightsaber);
			return (1);
		}
		i++;
	}
	return (0);
}

void	get_weapon_attack_sprite(t_game *g)
{
	if (init_lightsaber_attack_struct(g))
		return ;
	if (load_lightsaber_attack_textures(g))
		return ;
}
