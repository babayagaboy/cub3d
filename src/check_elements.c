/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:43:32 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/15 17:48:19 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	check_rbg(char *str)
{
	char	**splited;
	char	c[] = {',', '\0'};
	int		result;

	if (!str)
		return (0);
	splited = ft_split(str, c);
	if (!splited)
		return (0);
	result = validate_rgb_values(splited);
	free_memory(splited);
	return (result);
}

int	handle_texture(char *line, int value, t_ele_var *vars, char **tex_path)
{
	int	fd;

	fd = open(&line[5], O_RDONLY);
	vars->elements_found += value;
	if (fd >= 0)
	{
		vars->opened += value;
		*tex_path = ft_strdup(&line[5]);
		close(fd);
	}
	else
		return (0);
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

int	handle_floor_ceiling(char *line, int value, t_ele_var *vars, t_ori_tex *tex)
{
	int	type;
	int	fd;
	int	increment;

	vars->elements_found += value;
	type = f_c_type(&line[2]);
	if (value == 5)
		increment = 1;
	else
		increment = 2;
	if (type == 2)
	{
		fd = open(&line[4], O_RDONLY);
		if (fd >= 0)
		{
			vars->f_c_element += increment;
			choose_corect_path(line, value, tex);
			close(fd);
		}
		else
			return (0);
	}
	else
	{
		if (check_rbg(&line[2]))
			vars->f_c_element += increment;
		else
			return (0);
	}
	return (1);
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
		handle_floor_ceiling(line, 7, vars, tex);
}



int	check_elements(char **elements, t_ori_tex *tex)
{
	int	y;
	//int	elements_found;
	//int	opened;
	//int	f_c_element;

	t_ele_var	*vars;

	vars = malloc(sizeof(t_ele_var));
	if (!vars)
		return (0);

	if (!elements)
		return (0);
	y = 0;
	//elements_found = 0;
	//opened = 0;
	//f_c_element = 0;

	vars->elements_found = 0;
	vars->opened = 0;
	vars->f_c_element = 0;


	while (elements[y])
	{
		process_element_line(elements[y], vars, tex);
		y++;
	}
	if (vars->elements_found == 28 && vars->opened == 10 && vars->f_c_element == 5)
		return (1);
	return (0);
}


