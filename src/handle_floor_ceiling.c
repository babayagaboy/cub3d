/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:45:47 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/07 15:48:22 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_xpm_path_fc(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

void	get_fc(t_game *g, t_player *p, t_ori_tex *t, int i)
{
	int	j;

	if (i <= (SCREENHEIGHT >> 1))
		return ;
	init_floor_ceil_params(g->ray, p, i);
	j = 0;
	while (j < SCREENWIDTH)
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
	char	*path;

	buff = malloc(sizeof(char) * 10);
	if (!buff)
		return (0);
	path = &line[4];
	if (!is_xpm_path_fc(path))
		return (free(buff), 0);
	fd = open(path, O_RDONLY);
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

	increment = 2;
	vars->elements_found += value;
	type = f_c_type(&line[2]);
	if (value == 5)
		increment = 1;
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
