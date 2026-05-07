/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:43:32 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 20:25:36 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	check_rbg(char *str, int *arr)
{
	char	**splited;
	char	c[2];
	int		result;

	c[0] = ',';
	c[1] = '\0';
	if (!str)
		return (0);
	splited = ft_split(str, c);
	if (!splited)
		return (0);
	result = validate_rgb_values(splited, arr);
	free_memory(splited);
	return (result);
}

int	handle_texture(char *line, int value, t_ele_var *vars, char **tex_path)
{
	int		fd;
	size_t	rc;
	char	*buff;
	char	*path;

	buff = malloc(sizeof(char) * 10);
	if (!buff)
		return (0);
	path = &line[5];
	if (!is_xpm_path(path))
		return (free(buff), 0);
	fd = open(path, O_RDONLY);
	rc = read(fd, buff, 10);
	vars->elements_found += value;
	if (fd >= 0 && rc > 0)
	{
		vars->opened += value;
		*tex_path = ft_strdup(path);
		if (buff != NULL)
			free(buff);
		close(fd);
	}
	else
		return (free(buff), 0);
	return (1);
}

void	choose_corect_path(char *line, int value, t_ori_tex *tex)
{
	if (value == 5)
		tex->path_floor = ft_strdup(&line[4]);
	else if (value == 6)
		tex->path_ceiling = ft_strdup(&line[4]);
	else if (value == 7)
		tex->path_door = ft_strdup(&line[4]);
}

void	process_element_line(char *line, t_ele_var *vars, t_ori_tex *tex)
{
	if (ft_strncmp(line, "NO", 2) == 0 && line[2] == ' ')
		handle_texture(line, 1, vars, &tex->path_north);
	else if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
		handle_texture(line, 2, vars, &tex->path_south);
	else if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
		handle_texture(line, 3, vars, &tex->path_west);
	else if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
		handle_texture(line, 4, vars, &tex->path_east);
	else if (ft_strncmp(line, "F", 1) == 0 && line[1] == ' ')
		handle_floor_ceiling(line, 5, vars, tex);
	else if (ft_strncmp(line, "C", 1) == 0 && line[1] == ' ')
		handle_floor_ceiling(line, 6, vars, tex);
	else if (ft_strncmp(line, "D", 1) == 0 && line[1] == ' ')
	{
		vars->door_found = 1;
		handle_floor_ceiling(line, 7, vars, tex);
	}
}

int	check_elements(char **elements, t_ori_tex *tex, t_ele_var *vars)
{
	int		y;

	if (!elements)
		return (0);
	y = 0;
	while (elements[y])
	{
		process_element_line(elements[y], vars, tex);
		y++;
	}
	if (vars->door_found)
	{
		if (vars->elements_found == 28
			&& vars->opened == 10 && vars->f_c_element == 5)
			return (1);
	}
	else
	{
		if (vars->elements_found == 21
			&& vars->opened == 10 && vars->f_c_element == 3)
			return (1);
	}
	printf("Error\nElements data is corruped\n");
	return (0);
}
