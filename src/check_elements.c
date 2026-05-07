/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:43:32 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 17:10:42 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	is_xpm_path(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".xpm", 4) == 0);
}

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
	{
		if (!handle_texture(line, 1, vars, &tex->path_north))
			vars->stop = 1;
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
	{
		if (!handle_texture(line, 2, vars, &tex->path_south))
			vars->stop = 1;
	}
	else if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
	{
		if (!handle_texture(line, 3, vars, &tex->path_west))
			vars->stop = 1;
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
	{
		if (!handle_texture(line, 4, vars, &tex->path_east))
			vars->stop = 1;
	}
	else if (ft_strncmp(line, "F", 1) == 0 && line[1] == ' ')
	{
		if (!handle_floor_ceiling(line, 5, vars, tex))
			vars->stop = 1;
	}
	else if (ft_strncmp(line, "C", 1) == 0 && line[1] == ' ')
	{
		if (!handle_floor_ceiling(line, 6, vars, tex))
			vars->stop = 1;
	}
	else if (ft_strncmp(line, "D", 1) == 0 && line[1] == ' ')
	{
		vars->door_found = 1;
		if (!handle_floor_ceiling(line, 7, vars, tex))
			vars->stop = 1;
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
		printf("here\n");
		process_element_line(elements[y], vars, tex);
		y++;
	}
	if (vars->door_found)
	{
		printf("1: ele_found: %d\nopened: %d\nf_c_elemente:%d\n\n", vars->elements_found, vars->opened,  vars->f_c_element);
		if (vars->elements_found == 28
			&& vars->opened == 10 && vars->f_c_element == 5)
			return (1);
	}
	else
	{
		printf("2: ele_found: %d\nopened: %d\nf_c_elemente:%d\n\n", vars->elements_found, vars->opened,  vars->f_c_element);
		if (vars->elements_found == 21
			&& vars->opened == 10 && vars->f_c_element == 3)
			return (1);
	}
	printf("3: ele_found: %d\nopened: %d\nf_c_elemente:%d\n", vars->elements_found, vars->opened,  vars->f_c_element);
	return (0);
}
