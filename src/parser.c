#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

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


int	**get_spaces_coordinates(char **map)
{
	int	**space_coordenates;
	int	i;
	int	j;
	int	k;

	space_coordenates = malloc(sizeof(int *) * 100);
	if (!space_coordenates)
		return (0);
	i = 0;

	while (i < 30)
	{
		space_coordenates[i] = malloc(sizeof(int) * 2);
		if (!space_coordenates[i])
			return (free_int_arr(space_coordenates, i), NULL);
		i++;
	}

	i = 0;
	k = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				space_coordenates[k][0] = i;
				space_coordenates[k][1] = j;
				k++;
			}
			j++;
		}
		i++;
	}
	return (space_coordenates);
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

	return (0);
}