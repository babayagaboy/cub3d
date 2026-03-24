/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:30:38 by myivanov          #+#    #+#             */
/*   Updated: 2026/03/24 21:17:12 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/libft/libft.h"
#include <cub3d.h>

size_t	ft_nl_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	**read_file(char *file)
{
	char	**map;
	char	*buff;
	int		num_read;
	int	i;
	int	fd;
	int	count;
	int j;
	int	k;
	int	l;
	int	line_start;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return NULL;

	buff = malloc(sizeof(char) * 100000);
	if (!buff)
		return NULL;
	
	i = 0;
	num_read = read(fd, &buff[i], 1);
	if (num_read == -1)
		return (free(buff), NULL);
	while (num_read > 0 && i < 99998)
		num_read = read(fd, &buff[++i], 1);
	buff[i] = '\0';
	close(fd);
	
	count = 0;
	j = 0;
	while (buff[j])
	{
		if (buff[j] == '\n')
			count++;
		j++;
	}
	if (i > 0 && buff[i - 1] != '\n')
		count++;
	
	map = ft_calloc(count + 1, sizeof(char *));
	if (!map)
		return (free(buff), NULL);
	
	
	j = 0;
	k = 0;
	while (buff[j] && k < count)
	{
		line_start = j;
		l = 0;
		while (buff[j] && buff[j] != '\n')
		{
			l++;
			j++;
		}
		

		map[k] = malloc(sizeof(char) * (l + 1));
		if (!map[k])
			return (free_char_arr(map, k), free(buff), NULL);
		
		ft_strlcpy(map[k], &buff[line_start], l + 1);
		k++;
		
		if (buff[j] == '\n')
			j++;
	}
	map[k] = NULL;
	return (free(buff), map);
}


int	*get_player_coords(char **map)
{
	int	*player_coord;
	int	i;
	int	j;
	int	count;

	if (!map)
		return (0);

	i = 0;
	count = 0;
	player_coord = malloc(sizeof(int) * 2);
	if (!player_coord)
		return (NULL);
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
		return (free(player_coord), NULL);
	return (player_coord);
}

//check all 0 surrounding for spaces


int	check_walls(char **map, int y, int x)
{
	if (!map)
		return (0);
	int	count = 0;
	if (y > 0 && map[y - 1] && map[y - 1][x] && (map[y - 1][x] == '1' || map[y - 1][x] == '0')) // North
		count++;
	if (map[y + 1] && map[y + 1][x] && (map[y + 1][x] == '1' || map[y + 1][x] == '0')) // South
		count++;
	if (x > 0 && map[y][x - 1] && (map[y][x - 1] == '1' || map[y][x - 1] == '0')) // West
		count++;
	if (map[y][x + 1] && (map[y][x + 1] == '1' || map[y][x + 1] == '0')) // East
		count++;
	if (count == 4)
		return (1);
	printf("[%d][%d] = %d\n", y, x, count);
	return (0);
}

int	f_c_type(char *str)
{
	if (!ft_strncmp(str, "./", 2))
		return (2); //file type
	else
		return (1); //RGB type
}

int	check_rbg(char *str)
{
	char **splited;
	char	c[] = {',', '\0'};
	int	i;
	int	j;
	int	result;

	if (!str)
		return (0);

	splited = ft_split(str, c);
	if (!splited)
		return (0);
	i = 0;
	while (splited[i])
	{
		j = 0;
		while (splited[i][j])
		{
			if (!(splited[i][j] >= '0' && splited[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	i = 0;
	while (splited[i])
	{	
		result = ft_atoi(splited[i]);
		if (result < 0 || result > 255)
			return (0);
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}


int	check_elements(char **elements)
{
	int	elements_found;
	int	opened;
	int	open_test;
	int	y;
	int f_c_element = 0;
	int	type;

	if (!elements)
		return (0);

	y = 0;
	elements_found = 0;
	opened = 0;

	while (elements[y])
	{
		if (ft_strncmp(elements[y], "NO", 2) == 0 && elements[y][2] == ' ')
		{
			elements_found += 1;
			open_test = open(&elements[y][5], O_RDONLY);
			if (open_test >= 0)
			{
				opened += 1;
				close(open_test);
			}
			y++;
			continue;
			
		}
		if (ft_strncmp(elements[y], "SO", 2) == 0 && elements[y][2] == ' ')
		{
			elements_found += 2;
			open_test = open(&elements[y][5], O_RDONLY);
			if (open_test >= 0)
			{
				opened += 2;
				close(open_test);
			}
			y++;
			continue;
		}
		if (ft_strncmp(elements[y], "WE", 2) == 0 && elements[y][2] == ' ')
		{
			elements_found += 3;
			open_test = open(&elements[y][5], O_RDONLY);
			if (open_test >= 0)
			{
				opened += 3;
				close(open_test);
			}
			y++;
			continue;
		}
		if (ft_strncmp(elements[y], "EA", 2) == 0 && elements[y][2] == ' ')
		{
			elements_found += 4;
			open_test = open(&elements[y][5], O_RDONLY);
			if (open_test >= 0)
			{
				opened += 4;
				close(open_test);
			}
			y++;
			continue;
		}
		if (ft_strncmp(elements[y], "F", 1) == 0 && elements[y][1] == ' ')
		{
			elements_found += 5;
			type = f_c_type(&elements[y][2]);
			if (type == 2)
			{
				open_test = open(&elements[y][4], O_RDONLY);
				if (open_test >= 0)
				{
					f_c_element += 1;
					close(open_test);
				}
			}
			else
			{
				if (check_rbg(&elements[y][2]))
					f_c_element += 1;
			}
			y++;
			continue;
			
		}
		if (ft_strncmp(elements[y], "C", 1) == 0 && elements[y][1] == ' ')
		{
			elements_found += 6;
			type = f_c_type(&elements[y][2]);
			if (type == 2)
			{
				open_test = open(&elements[y][4], O_RDONLY);
				if (open_test >= 0)
				{
					f_c_element += 2;
					close(open_test);
				}
				
			}
			else
			{
				if (check_rbg(&elements[y][2]))
					f_c_element += 2;
			}
			y++;
			continue;
		}
		y++;
	}
	if (elements_found == 21 && opened == 10 && f_c_element == 3)
			return (1);
	return (0);
}

int	check_map(char **map, t_player *p)
{
	int		y = 0;
	int		x = 0;
	int		*player_coords;
	char	player_orientation;

	if (!map || !map[0])
		return (0);
	
	player_coords = get_player_coords(map); //to do save in (pos_y, pos_x)
	if (!player_coords)
		return (0);

	player_orientation = map[player_coords[0]][player_coords[1]];
	map[player_coords[0]][player_coords[1]] = '0';

	while(map[0][x] != '\0')
	{
		if(map[0][x] == '0')
			return (free(player_coords), 0);
		x++;
	}

	while(map[y])
	{
		if(map[y][0] == '0')
			return (free(player_coords), 0);
		y++;
	}
	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == '0' && check_walls(map, y, x) == 0)
				return (free(player_coords), 0);
			x++;
		}
		y++;
	}
	map[player_coords[0]][player_coords[1]] = player_orientation; 	//to do (dir_y, dir_x) = get_player_orientation()
	p->pos_y = (double)player_coords[0];
	p->pos_x = (double)player_coords[1];
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
	char	**splited;
	char	*cleaned;
	int		size_to_malloc;
	int		k;
	int		l;
	int		total_chars;
	int		m;
	char	c[] = {' ', '\t', '\b', '\f', '\r', '\0'};

	if (!str)
		return (NULL);

	splited = ft_split(str, c);
	if (!splited)
		return (NULL);

	k = 0;
	total_chars = 0;
	while (splited[k])
	{
		l = 0;
		while (splited[k][l])
			l++;
		total_chars += l;
		k++;
	}

	if (k > 0)
		size_to_malloc = total_chars + (k - 1);
	else
		size_to_malloc = 0;

	cleaned = malloc(sizeof(char) * (size_to_malloc + 1));
	if (!cleaned)
		return (free_memory(splited), NULL);

	k = 0;
	m = 0;
	while (splited[k])
	{
		l = 0;
		while (splited[k][l])
			cleaned[m++] = splited[k][l++];
		if (splited[k + 1] && splited[k][--l] != ',')
			cleaned[m++] = ' ';
		k++;
	}
	cleaned[m] = '\0';
	return (free_char_arr(splited, k), cleaned);
}


char	**get_elements(char **cub, int *y)
{
	char	**elements_file;
	int	i;
	int	count;
	int	j;

	if (!cub)
		return NULL;

	j = 0;
	count = 0;
	while (cub[j])
	{
		if (cub[j] && (ft_isempty(cub[j]) || cub[j][0] == '\n'))
		{
			j++;
			continue;
		}
		if (ft_strnstr(ft_findspace(cub[*y]), "C", 1))
		{
			count++;
			j++;
			break ;
		}
		count++;
		j++;
	}

	elements_file = malloc(sizeof(char *) * (count + 2));
	if (!elements_file)
		return (NULL);
	i = 0;
	int	stop = 0;
	while (cub[*y])
	{
		if (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n'))
		{
			(*y)++;
			continue;
		}
		if (ft_strnstr(ft_findspace(cub[*y]), "C", 1))
			stop = 1;
		elements_file[i] = looksmax_string(ft_findspace(cub[*y]));
		if (!elements_file[i])
			return (free_char_arr(elements_file, i), NULL);
		(*y)++;
		if (stop)
			break ;
		i++;
	}
	elements_file[i + 1] = NULL;
	return (elements_file);
}

char	**get_map(char **cub, int *y)
{
	char	**map;
	int	i;
	int	k;
	int	count;

	if (!cub)
		return (NULL);


	while (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n')) //Skips all initial white spaces after elements
		(*y)++;
	
	k = *y;
	count = 0;
	while (cub[k] && !(ft_isempty(cub[k]) || cub[k][0] == '\n')) //line count to malloc
	{
		count++;
		k++;
	}
	map = ft_calloc((count + 1), sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	k = *y;
	while (i < count && cub[k])
	{
		map[i] = ft_calloc((ft_strlen(cub[k]) + 1), sizeof(char));
		if (!map[i])
			return (free_char_arr(map, i), NULL);
		ft_strlcpy(map[i], cub[k], ft_strlen(cub[k]) + 1);
		i++;
		k++;
	}
	map[i] = NULL;
	return map;
}

int	parser(int argc, char *argv[], t_game *g)
{
	char	*file;
	int	y;
    
	if (argc != 2)
    return (0);	
    
	file = argv[1];
	if (!(ft_strnstr(file, ".cub", ft_strlen(file))))
		return (0);
        
        g->cub = read_file(file);
        if (!g->cub)
        {
            printf("Cub failed!\n");
		return (0);
	}
	y = 0;
	g->elements_file = get_elements(g->cub, &y);
	if (!g->elements_file)
	{
        printf("elements_file failed!\n");
		free_memory(g->cub);
		return (0);
	}
	g->map = get_map(g->cub, &y);
	if (!g->map)
	{
        printf("map failed!\n");
		free_memory(g->cub);
		free_memory(g->elements_file);
		return (0);
	}
    
	printf(".CUB FILE:\n");
	for (int i = 0; g->cub[i]; i++)
	{
        for (int j = 0; g->cub[i][j]; j++)
        printf("%c", g->cub[i][j]);
		printf("\n");
	}
	printf("ELEMENTS_FILE:\n");
	for (int i = 0; g->elements_file[i]; i++)
	{
        for (int j = 0; g->elements_file[i][j]; j++)
        printf("%c", g->elements_file[i][j]);
		printf("\n");
	}
	printf("MAP:\n");
	for (int i = 0; g->map[i]; i++)
	{
		for (int j = 0; g->map[i][j]; j++)
        printf("%c", g->map[i][j]);
		printf("\n");
	}
	if (!check_elements(g->elements_file))
	{
        printf("Elements file faild\n");
		free_memory(g->cub);
		free_memory(g->elements_file);
		free_memory(g->map);
		return (0);
	}
	if (!check_map(g->map, g->player))
	{
        printf("Map file faild\n");
		free_memory(g->cub);
		free_memory(g->elements_file);
		free_memory(g->map);
		return (0);
	}
	else
    	printf("GOOD GOY\n");
    free_memory(g->cub);
	return (1);
}
