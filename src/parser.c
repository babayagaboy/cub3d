/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:30:38 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/06 15:26:51 by myivanov         ###   ########.fr       */
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

int	load_elements_and_map(t_game *g)
{
	int	y;

	y = 0;
	g->elements_file = get_elements(g->cub, &y);
	if (!g->elements_file)
	{
		printf("elements_file failed!\n");
		return (0);
	}
	g->map = get_map(g->cub, &y);
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
	if (!validate_args(argc, argv))
		return (0);
	if (!load_cub_file(g, argv[1]))
		return (0);
	if (!load_elements_and_map(g))
		return (free_memory(g->cub), 0);
	print_debug(g);
	if (!check_elements(g->elements_file))
		return (printf("Elements file failed\n"), free_all(g), 0);
	if (!check_map(g->map, g->player))
		return (printf("Map file failed\n"), free_all(g), 0);
	printf("GOOD GOY\n");
	free_memory(g->cub);
	return (1);
}

