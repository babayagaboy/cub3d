/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 16:30:38 by myivanov          #+#    #+#             */
/*   Updated: 2026/03/20 15:20:27 by myivanov         ###   ########.fr       */
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


char	**read_file(char *file)
{
	char	**map;
	char	*buff;
	int		num_read;
	int	i;
	int	fd;

	int	count;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return NULL;

	line = get_next_line(fd);
	if (!line)
		return NULL;
	count = 0;
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return NULL;
	i = 0;
	map = malloc(sizeof(char *) * (count + 1));
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (i < count && line)
	{
		map[i] = malloc(sizeof(char) * (ft_nl_strlen(line) + 1));
		if (!map[i])
			return (free_char_arr(map, i), NULL);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return NULL;
	i = 0;
	buff = malloc(sizeof(char *) * 100000);
	if (!buff)
		return (NULL);
	num_read = read(fd, &buff[i], 1);
	while (num_read > 0)
		num_read = read(fd, &buff[++i], 1);
	buff[i] = '\0';


	printf("ORIGINAL BUFFER: %s\n", buff);
	
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
		return (free(player_coord), NULL);
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

	y = 0;
	elements_found = 0;
	opened = 0;

	printf("In check_elemets: ELEMENTS FILE:\n");
	for (int i = 0; elements[i]; i++)
	{
		for (int j = 0; elements[i][j]; j++)
			printf("%c", elements[i][j]);
		printf("\n");
	}
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
	printf("ABOUT TO RETURN FROM CHECK_ELEMENTS\n");
	if (elements_found == 21 && opened == 10 && f_c_element == 3)
			return (1);
	return (0);
}



int	check_map(char **map)
{
	int		y = 0;
	int		x = 0;
	int		*player_coords;
	char	player_orientation;
	
	player_coords = get_player_coords(map); //to do save in (pos_y, pos_x)
	if (!player_coords)
		return (0);
	printf("In check_map: AFTER PLAYER_COORDS\n");

	player_orientation = map[player_coords[0]][player_coords[1]];
	map[player_coords[0]][player_coords[1]] = '0';
	printf("In check_map: MAP VIEW\n");
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
	while(map[0][x] != '\0')
	{
		if(map[0][x] == '0')
			return (0);
		x++;
	}
	printf("After first while x\n");

	while(map[y][0] != '\0')
	{
		printf("map[%d]: %c\n",y, map[y][0]);
		if(map[y][0] == '0')
			return (0);
		y++;
	}
	printf("After first while y\n");

	y = 1;
	while (map[y])
	{
		x = 1;
		while (map[y][x])
		{
			if (map[y][x] == '0' && check_walls(map, y, x) == 0)
				return (0);
			x++;
		}
		y++;
	}
	printf("ABOUT TO RETURN FROM check_map\n");
	map[player_coords[0]][player_coords[1]] = player_orientation; 	//to do (dir_y, dir_x) = get_player_orientation()
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
		return (free_char_arr(splited, k), NULL);

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
	int	j;
	int	x;
	int	k;
	int	count;

	printf("ENTERED GET_MAP\n");

	while (cub[*y] && (ft_isempty(cub[*y]) || cub[*y][0] == '\n'))
		(*y)++;
	
	printf("AFTER 1st WHILE TO CLEAR OFF THE NEW LINTES\n");

	k = *y;
	count = 0;
	while (cub[k])
	{
		count++;
		k++;
	}

	printf("AFTER THE COUNT WHILE. COUNT: %d\n", count);


	map = ft_calloc(count + 1, sizeof(char *));
	if (!map)
		return (NULL);
	printf("ALOCATED MAP FOR A TOTAL OF %lu BYTES\n", sizeof(map));	
	i = 0;
	k = *y;
	while (i < count)
	{
		map[i] = ft_calloc((ft_strlen(cub[k]) + 1), sizeof(char));
		if (!map[i])
			return (free_char_arr(map, i), NULL);
		printf("MAP[%d]: with a size of %lu\n", i, ft_strlen(cub[k] + 1));
		i++;
		k++;
	}

	printf("MEMORY ALLOCATION SUCESSFUL\n");

	i = 0;
	while (cub[*y])
	{
		printf("cub[%d]: %s\n", *y, cub[*y]);
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
	printf("At the end of the fucking while cub*y loop\n");
	printf("After putting map[i][j] = '0' \n");
	map[i + 1] = NULL;
	printf("After map[i + 1] = NULL;\n");
	return map;
}

void	free_memory(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free (arr);
}


int main(int argc, char *argv[])
{
	char	*file;
	char	**cub;
	char	**elements_file;
	char	**map;
	int	y;

	if (argc != 2)
		return (0);	

	file = argv[1];
	if (!(ft_strnstr(file, ".cub", ft_strlen(file))))
		return (0);
	
	cub = read_file(file);
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

	/*printf(".CUB FILE:\n");
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
	}*/
	
	printf("OK BACK AT MAIN: NOW ENTERING CHECK_ELEMENTS\n");
	
	if (!check_elements(elements_file))
	{
		printf("Elements file faild\n");
		return (0);
	}
	printf("OK BACK AT MAIN: NOW ENTERING CHECK_MAP\n");
	if (!check_map(map))
	{
		printf("Map file faild\n");
		return (0);
	}
	else
		printf("GOOD GOY\n");
	
	free_memory(cub);
	free_memory(elements_file);
	free_memory(map);
	return (0);
}