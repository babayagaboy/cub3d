/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:44:20 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/07 20:33:23 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

void	fmi(int **arr)
{
	int	i;

	if (!arr)
		return ;
	i = SCREENHEIGHT - 1;
	while (i >= 0)
		free(arr[i--]);
	free (arr);
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

void	free_t_texture(t_texture *tex, t_mlx *mlx, char *path)
{
	if (!tex)
		return ;
	if (tex->img_ptr && mlx && mlx->mlx)
	{
		mlx_destroy_image(mlx->mlx, tex->img_ptr);
		if (path)
			free(path);
	}
	free(tex);
}
