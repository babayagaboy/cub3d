/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:00:20 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 13:44:16 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	count_elements(char **cub, int y, int *door_found)
{
	int		count;
	char	*clean;

	count = 0;
	while (cub[y])
	{
		if (cub[y] && (ft_isempty(cub[y]) || cub[y][0] == '\n'))
		{
			y++;
			continue ;
		}
		clean = ft_findspace(cub[y]);
		if (ft_strncmp(clean, "D", 1) == 0)
			*door_found = 1;
		count++;
		if (*door_found == 1 && count == 8)
			break ;
		else if (*door_found != 1 && count == 7)
			break ;
		y++;
	}
	return (count);
}

int	process_line(char *line, char **elements_file,
	int i, t_ele_var *v)
{
	char	*clean;
	int		find_stop;

	clean = ft_findspace(line);
	if (v->door_found == 1)
		find_stop = 6;
	else
		find_stop = 5;
	if (i > find_stop)
	{
		v->stop = 1;
		return (1);
	}
	elements_file[i] = looksmax_string(clean);
	if (!elements_file[i])
		return (0);
	return (1);
}

char	**fill_elements(char **cub, int *y, int count, t_ele_var *v)
{
	char	**elements_file;
	int		i;

	elements_file = ft_calloc(count + 2, sizeof(char *));
	if (!elements_file)
		return (NULL);
	i = 0;
	v->stop = 0;
	while (cub[*y])
	{
		if (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n'))
		{
			(*y)++;
			continue ;
		}
		if (!process_line(cub[*y], elements_file, i, v))
			return (free_char_arr(elements_file, i), NULL);
		if (v->stop)
			break ;
		(*y)++;
		i++;
	}
	elements_file[i] = NULL;
	return (elements_file);
}

char	**get_elements(char **cub, int *y, t_ele_var *vars)
{
	char	**elements_file;
	int		count;

	if (!cub)
		return (NULL);
	count = count_elements(cub, *y, &vars->door_found);
	elements_file = fill_elements(cub, y, count, vars);
	return (elements_file);
}
