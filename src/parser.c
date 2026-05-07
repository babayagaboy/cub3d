/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:30:38 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 19:29:12 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	validate_args(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	if (!is_cub_path(argv[1]))
		return (0);
	return (1);
}

int	load_cub_file(t_game *g, char *file)
{
	g->cub = read_file(file);
	if (!g->cub)
		return (0);
	return (1);
}

int	load_elements_and_map(t_game *g, t_ele_var *vars)
{
	int	y;

	y = 0;
	g->elements_file = get_elements(g->cub, &y, vars);
	if (!g->elements_file)
	{
		printf("Error\nElements file failed\n");
		return (0);
	}
	g->map = get_map(g->cub, &y, g);
	if (!g->map)
	{
		printf("Error\nMap file filed\n");
		free_memory(g->elements_file);
		return (0);
	}
	return (1);
}

void	free_all(t_game *g)
{
	free_memory(g->cub);
	free_memory(g->elements_file);
	free_memory(g->map);
	if (!g->o_text)
		return ;
	if (g->o_text->path_ceiling)
		free(g->o_text->path_ceiling);
	if (g->o_text->path_floor)
		free(g->o_text->path_floor);
	if (g->o_text->path_door)
		free(g->o_text->path_door);
	if (g->o_text->path_north)
		free(g->o_text->path_north);
	if (g->o_text->path_east)
		free(g->o_text->path_east);
	if (g->o_text->path_south)
		free(g->o_text->path_south);
	if (g->o_text->path_west)
		free(g->o_text->path_west);
}

int	parser(int argc, char *argv[], t_game *g)
{
	t_ele_var	*vars;

	vars = malloc(sizeof(t_ele_var));
	if (!vars)
		return (0);
	vars->elements_found = 0;
	vars->opened = 0;
	vars->f_c_element = 0;
	vars->door_found = 0;
	vars->stop = 0;
	if (!validate_args(argc, argv))
		return (printf("Error\nArguments error\n"), free(vars), 0);
	if (!load_cub_file(g, argv[1]))
		return (printf("Error\n.cub file filed\n"), free(vars), 0);
	if (!load_elements_and_map(g, vars))
		return (free_memory(g->cub), free(vars), 0);
	if (!check_elements(g->elements_file, g->o_text, vars))
		return (free_all(g), free(vars), 0);
	if (!check_map(g->map, g->player, g, vars))
		return (free_all(g), free(vars), 0);
	free_memory(g->cub);
	free(vars);
	return (1);
}
