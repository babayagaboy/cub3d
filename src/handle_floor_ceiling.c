/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 22:45:47 by hgutterr          #+#    #+#             */
/*   Updated: 2026/05/05 22:56:31 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	handle_path(char *line, int value, t_ori_tex *tex)
{
	char	*buff;
	int		fd;
	size_t	rc;

	buff = malloc(sizeof(char) * 10);
	if (!buff)
		return ;
	fd = open(&line[4], O_RDONLY);
	rc = read(fd, buff, 10);
	if (fd >= 0 && buff != NULL)
	{
		choose_corect_path(line, value, tex);
		free(buff);
		close(fd);
	}
	else
		free(buff);
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
		handle_path(line, value, tex);
		vars->f_c_element += increment;
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
