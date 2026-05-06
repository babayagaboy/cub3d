/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:45:47 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/06 18:37:47 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_fc(t_game *g, t_player *p, t_ori_tex *t, int i)
{
	int	j;

	if (i <= (screenHeight >> 1))
    	return ;

	init_floor_ceil_params(g->ray, p, i);

	j = 0;
	while (j < screenWidth)
	{
		if (t->path_ceiling)
			draw_ceil_pixel(t, g, i, j);
		if (t->path_floor)
			draw_floor_pixel(t, g, i, j);

		g->ray->floor_x += g->ray->floor_step_x;
		g->ray->floor_y += g->ray->floor_step_y;
		++j;
	}
}

int	handle_path(char *line, int value, t_ori_tex *tex)
{
	char	*buff;
	int		fd;
	size_t	rc;

	buff = malloc(sizeof(char) * 10);
	if (!buff)
		return (0);
	fd = open(&line[4], O_RDONLY);
	rc = read(fd, buff, 10);
	if (fd >= 0 && rc >= 1)
	{
		choose_corect_path(line, value, tex);
		free(buff);
		close(fd);
	}
	else
		return (free(buff), 0);
	return (1);
}

int	handle_floor_ceiling(char *line, int value, t_ele_var *vars, t_ori_tex *tex)
{
	int		type;
	int		increment;

	vars->elements_found += value;
	type = f_c_type(&line[2]);
	if (value == 5)
		increment = 1;
	else
		increment = 2;
	if (type == 2)
	{
		if (handle_path(line, value, tex))
			vars->f_c_element += increment;
		else
			return (0);
	}
	else
	{
		if (value == 5 && check_rbg(&line[2], tex->rgb_floor))
			vars->f_c_element += increment;
		if (value == 6 && check_rbg(&line[2], tex->rgb_ceiling))
			vars->f_c_element += increment;
		else
			return (0);
	}
	return (1);
}
