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


char	**read_map(int fd)
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

//white spaces teem que estar rodeados por walls.


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

int	check_map(char **map)
{
	int		y = 1;
	int		x = 1;
	int		*player_coords;
	
	player_coords = get_player_coords(map);
	if (!player_coords)
		return (0);

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
	map[player_coords[0]][player_coords[1]] = 'N';
	return (1);
}

int main(int argc, char *argv[])
{
	char	*file;
	int		fd;
	char	**map;

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
	map = read_map(fd);
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
	if (check_map(map))
		printf("Great map\n");
	else
		printf("Shit map\n");

	return (0);
}