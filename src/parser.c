/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:30:38 by myivanov          #+#    #+#             */
/*   Updated: 2026/03/17 18:28:59 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"
#include <cub3d.h>

void	free_char_arr(char **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

void	free_int_arr(int **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}


char	**read_file(int fd)
{
	char	**map;
	char	*buff;
	int		num_read;
	int	i;

	i = 0;
	map = malloc(sizeof(char *) * 1000);
	if (!map)
		return (NULL);
	while (i < 1000)
	{
		map[i] = malloc(sizeof(char) * 10000);
		if (!map[i])
			return (free_char_arr(map, i), NULL);
		i++;
	}
	i = 0;
	buff = malloc(sizeof(char) * 100000);
	if (!buff)
		return (NULL);
	num_read = read(fd, &buff[i], 1);
	while (num_read > 0)
		num_read = read(fd, &buff[++i], 1);
	buff[i] = '\0';
	
	int j;
	int	k;
	int	l;

	j = 0;
	k = 0;
	l = 0;
	while (buff[j])
	{
		if (buff[j] == '\n')
		{
			map[k][l] = '\0';
			k++;
			l = 0;
			j++;
			continue ;
		}
		map[k][l]= buff[j];
		j++;
		l++;
	}
	map[k][l] = '\0';	
	map[k + 1] = NULL;
	return (free (buff), map);
}


int	*get_player_coords(char **map)
{
	int	*player_coord;
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	player_coord = malloc(sizeof(int) * 2);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
			{
				player_coord[0] = i; //y
				player_coord[1] = j; //x
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return NULL;
	return (player_coord);
}

//check all 0 surrounding for spaces


int	check_walls(char **map, int y, int x)
{
	int	count = 0;
	if (map[y - 1][x] == '1' || map[y - 1][x] == '0') // North
		count++;
	if (map[y + 1][x] == '1' || map[y + 1][x] == '0') // South
		count++;
	if (map[y][x - 1] == '1' || map[y][x - 1] == '0') // West
		count++;
	if (map[y][x + 1] == '1' || map[y][x + 1] == '0') // East
		count++;
	if (count == 4)
		return (1);
	printf("[%d][%d] = %d\n", y, x, count);
	return (0);
}



size_t	ft_nl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}


/*int	check_all_elements_present(char **map, int *y)
{
	int	elements_found;
	int	opened;
	int	open_test;

	elements_found = 0;
	opened = 0;
	while (map[*y])
	{
		if (ft_strnstr(map[*y], "NO", ft_nl_strlen(map[*y])) && ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])))
		{
			elements_found += 1;
			open_test = open(ft_substr(map[*y], ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])), ft_nl_strlen(map[*y])), O_RDONLY);
			if (open_test > 0)
				opened += 1;
			y++;
			continue;
		}
		if (ft_strnstr(map[*y], "SO", ft_nl_strlen(map[*y])) && ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])))
		{
			elements_found += 2;
			open_test = open(ft_substr(map[*y], ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])), ft_nl_strlen(map[*y])), O_RDONLY);
			if (open_test > 0)
				opened += 2;
			y++;
			continue;
			
		}
		if (ft_strnstr(map[*y], "WE", ft_nl_strlen(map[*y])) && ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])))
		{
			elements_found += 3;
			open_test = open(ft_substr(map[*y], ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])), ft_nl_strlen(map[*y])), O_RDONLY);
			if (open_test > 0)
				opened += 3;
			y++;
			continue;
		}
		if (ft_strnstr(map[*y], "EA", ft_nl_strlen(map[*y])) && ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])))
		{
			elements_found += 4;
			open_test = open(ft_substr(map[*y], ft_strnstr(map[*y], "./", ft_nl_strlen(map[*y])), ft_nl_strlen(map[*y])), O_RDONLY);
			if (open_test > 0)
				opened += 4;
			y++;
			continue;
		}
		if (ft_strnstr(map[*y], "F", ft_nl_strlen(map[*y])))
		{
			elements_found += 5;
			y++;
			continue;
		}
		if (ft_strnstr(map[*y], "C", ft_nl_strlen(map[*y])))
		{
			elements_found += 6;
			y++;
			break;
		}
	}
	if (elements_found == 21 && opened == 10)
		return (1);
	return (0);
}*/



int	check_map(char **map)
{
	int		y = 1;
	int		x = 1;
	int		*player_coords;
	char	player_orientation;
	
	player_coords = get_player_coords(map); //to do save in (pos_y, pos_x)
	if (!player_coords)
		return (0);

	player_orientation = map[player_coords[0]][player_coords[1]];
	map[player_coords[0]][player_coords[1]] = '0';
	while(map[0][x] != '\0')
	{
		if(map[0][x] == '0')
		{
			printf("here1\n");
			return (0);
		}
		x++;
	}

	while(map[y][0] != '\0')
	{
		if(map[y][0] == '0')
		{
			printf("here2\n");
			return (0);
		}
		y++;
	}

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			if (map[y][x] == '0' && check_walls(map, y, x) == 0)
			{
				printf("here3\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	map[player_coords[0]][player_coords[1]] = player_orientation; //to do (dir_y, dir_x) = get_player_orientation()
	return (1);
}
char	*ft_findspace(char *str)
{
	int i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return(&str[i]);
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

char	*looksmax_string(char *str)
{
	int		i;
	int		start2;
	int		len1;
	int		len2;
	int		j;
	char	*str1;
	char	*str2;
	char	*cleaned;

	if (!str)
		return (NULL);

	i = 0;
	while (str[i] && is_space(str[i]))
		i++;
	start2 = i;

	while (str[i] && !is_space(str[i]))
		i++;
	len1 = i - start2;

	while (str[i] && is_space(str[i]))
		i++;
	start2 = i;

	while (str[i] && !is_space(str[i]))
		i++;
	len2 = i - start2;

	str1 = malloc(len1 + 2);
	str2 = malloc(len2 + 1);
	if (!str1 || !str2)
		return (free(str1), free(str2), NULL);

	i = 0;
	while (i < len1)
	{
		str1[i] = str[i];
		i++;
	}
	str1[i++] = ' ';
	str1[i] = '\0';

	j = 0;
	while (j < len2)
	{
		str2[j] = str[start2 + j];
		j++;
	}
	str2[j] = '\0';

	cleaned = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (cleaned);
}


char	**get_elements(char **cub, int *y)
{
	char	**elements_file;
	int	i;
	int	j;
	int	x;

	elements_file = malloc(sizeof(char *) * 500);
	if (!elements_file)
		return (NULL);
	i = 0;
	while (i < 500)
	{
		elements_file[i] = malloc(sizeof(char) * 1000);
		if (!elements_file[i])
			return (free_char_arr(elements_file, i), NULL);
		i++;
	}

	i = 0;
	int	stop = 0;
	while (cub[*y])
	{
		x = 0;
		j = 0;
		while (cub[*y][x])
		{
			if (ft_strnstr(ft_findspace(cub[*y]), "C", 1))
				stop = 1;
			elements_file[i] = ft_strdup(ft_findspace(cub[*y]));
			if (!elements_file[i])
				return (free_char_arr(elements_file, i), NULL);
			j++;
			x++;
		}
		elements_file[i][j] = '\0';
		(*y)++;
		if (stop)
			break ;
		i++;
	}
	elements_file[i][j] = '\0';
	elements_file[i + 1] = NULL;
	return (elements_file);
}

char	**get_map(char **cub, int *y)
{
	char	**map;
	int	i;
	int	j;
	int	x;

	map = malloc(sizeof(char *) * 1000);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 500)
	{
		map[i] = malloc(sizeof(char) * 1000);
		if (!map[i])
			return (free_char_arr(map, i), NULL);
		i++;
	}

	while (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n'))
		(*y)++;

	i = 0;
	while (cub[*y])
	{
		x = 0;
		j = 0;
		while (cub[*y][x])
		{
			map[i][j] = cub[*y][x];
			j++;
			x++;
		}
		map[i][j] = '\0';
		(*y)++;
		i++;
	}
	map[i][j] = '\0';
	map[i] = NULL;
	return map;
}


int main(int argc, char *argv[])
{
	char	*file;
	int		fd;
	char	**cub;
	char	**elements_file;
	char	**map;
	int	y;

	if (argc != 2)
		return (0);	

	file = argv[1];
	if (!(ft_strnstr(file, ".cub", ft_strlen(file))))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1) 
	{
		printf("Error. Could not open file\n");
		return (0);
	}
	printf("File found, fd is %d\n", fd);
	cub = read_file(fd);
	if (!cub)
	{
		printf("Cub failed!\n");
		return (0);
	}
	y = 0;
	elements_file = get_elements(cub, &y);
	if (!elements_file)
	{
		printf("elements_file failed!\n");
		return (0);
	}
	map = get_map(cub, &y);
	if (!map)
	{
		printf("map failed!\n");
		return (0);
	}

	printf(".CUB FILE:\n");
	for (int i = 0; cub[i]; i++)
	{
		for (int j = 0; cub[i][j]; j++)
			printf("%c", cub[i][j]);
		printf("\n");
	}
	printf("ELEMENTS_FILE:\n");
	for (int i = 0; elements_file[i]; i++)
	{
		for (int j = 0; elements_file[i][j]; j++)
			printf("%c", elements_file[i][j]);
		printf("\n");
	}
	printf("MAP:\n");
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
	/*if (check_map(cub))
		printf("Great map\n");
	else
		printf("Shit map\n");*/

	return (0);
}