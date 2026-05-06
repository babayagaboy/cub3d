/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_guns_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 13:04:34 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:32:02 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*get_lightsaber_texture_path(int i)
{
	if (i == 0)
		return ("./assets/lightsaber_equip1.xpm");
	else if (i == 1)
		return ("./assets/lightsaber_equip2.xpm");
	else if (i == 2)
		return ("./assets/lightsaber_equip3.xpm");
	else if (i == 3)
		return ("./assets/lightsaber_equip4.xpm");
	else if (i == 4)
		return ("./assets/lightsaber_equip5.xpm");
	else
		return ("./assets/lightsaber_equip6.xpm");
}

int	init_lightsaber_struct(t_game *g)
{
	g->lightsaber = malloc(sizeof(t_weapon));
	if (!g->lightsaber)
		return (1);
	g->lightsaber->tex_arr = ft_calloc(7, sizeof(t_texture *));
	if (!g->lightsaber->tex_arr)
	{
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

int	load_lightsaber_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		load_texture(g->mlx, &g->lightsaber->tex_arr[i],
			get_lightsaber_texture_path(i));
		if (!g->lightsaber->tex_arr[i])
		{
			free_weapon(g->lightsaber, g->mlx);
			free(g->lightsaber);
			return (1);
		}
		i++;
	}
	return (0);
}

void	get_guns_sprite(t_game *g)
{
	if (init_lightsaber_struct(g))
		return ;
	if (load_lightsaber_textures(g))
		return ;
}
