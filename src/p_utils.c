/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:10:27 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 00:54:22 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	find_player(char **map, int *coord)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				coord[0] = i;
				coord[1] = j;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

char	*ft_findspace(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (&str[i]);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_walkable_tile(t_game *g, int y, int x)
{
	t_door	*door;

	if (!g->map[y] || !g->map[y][x])
		return (0);
	if (g->map[y][x] == '0')
		return (1);
	if (g->map[y][x] != 'D')
		return (0);
	door = find_door(g, y, x);
	if (!door)
		return (0);
	return (door->open_pct >= 0.9);
}

int	get_color(int r, int g, int b)
{
	return (r * (256 * 256) + g * 256 + b);
}
