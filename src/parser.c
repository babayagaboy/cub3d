/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:30:38 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/21 16:22:26 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"
#include <cub3d.h>


int	validate_args(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (0);
	return (1);
}

int	load_cub_file(t_game *g, char *file)
{
	g->cub = read_file(file);
	if (!g->cub)
	{
		printf("Cub failed!\n");
		return (0);
	}
	return (1);
}

int	load_elements_and_map(t_game *g, t_ele_var *vars)
{
	int	y;

	y = 0;
	g->elements_file = get_elements(g->cub, &y, vars);
	if (!g->elements_file)
	{
		printf("elements_file failed!\n");
		return (0);
	}
	g->map = get_map(g->cub, &y, g);
	if (!g->map)
	{
		free_memory(g->elements_file);
		printf("map failed!\n");
		return (0);
	}
	return (1);
}

void	print_debug(t_game *g)
{
	int i, j;

	printf(".CUB FILE:\n");
	for (i = 0; g->cub[i]; i++)
	{
		for (j = 0; g->cub[i][j]; j++)
			printf("%c", g->cub[i][j]);
		printf("\n");
	}
	printf("ELEMENTS_FILE:\n");
	for (i = 0; g->elements_file[i]; i++)
	{
		for (j = 0; g->elements_file[i][j]; j++)
			printf("%c", g->elements_file[i][j]);
		printf("\n");
	}
	printf("MAP:\n");
	for (i = 0; g->map[i]; i++)
	{
		for (j = 0; g->map[i][j]; j++)
			printf("%c", g->map[i][j]);
		printf("\n");
	}
}

void	free_all(t_game *g)
{
	free_memory(g->cub);
	free_memory(g->elements_file);
	free_memory(g->map);
}

int	parser(int argc, char *argv[], t_game *g)
{
	t_ele_var *vars;

	vars = malloc(sizeof(t_ele_var));
	if (!vars)
		return (0);

	vars->elements_found = 0;
	vars->opened = 0;
	vars->f_c_element = 0;
	vars->door_found = 0;

	if (!validate_args(argc, argv))
		return (0);
	if (!load_cub_file(g, argv[1]))
		return (0);
	if (!load_elements_and_map(g, vars))
		return (free_memory(g->cub), 0);
	print_debug(g);
	if (!check_elements(g->elements_file, g->o_text, vars))
		return (printf("Elements file failed\n"), free_all(g), 0);
	if (!check_map(g->map, g->player, g, vars))
		return (printf("Map file failed\n"), free_all(g), 0);
	if (!get_textures(g->mlx, g->o_text))
		return (printf("Textures failed\n"), free_all(g), 0);
	/*for (int i = 0; i < 3; ++i)
		printf("In parser rbg_ceiling[%d]: %d\n", i, g->o_text->rgb_ceiling[i]);
	printf("\n");
	for (int i = 0; i < 3; ++i)
		printf("In parser rbg_floor[%d]: %d\n", i, g->o_text->rgb_floor[i]);
	printf("GOOD GOY\n");*/
	free_memory(g->cub);
	return (1);
}

