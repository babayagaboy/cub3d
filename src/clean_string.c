/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:04:39 by myivanov          #+#    #+#             */
/*   Updated: 2026/05/05 23:32:30 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	calc_clean_size(char **splited)
{
	int	k;
	int	total_chars;
	int	l;

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
		return (total_chars + (k - 1));
	return (0);
}

void	copy_cleaned(char **splited, char *cleaned)
{
	int	k;
	int	l;
	int	m;

	k = 0;
	m = 0;
	while (splited[k])
	{
		l = 0;
		while (splited[k][l])
		{
			cleaned[m++] = splited[k][l++];
		}
		if (splited[k + 1] && splited[k][l - 1] != ',')
			cleaned[m++] = ' ';
		k++;
	}
	cleaned[m] = '\0';
}

char	*looksmax_string(char *str)
{
	char	**splited;
	char	*cleaned;
	int		size;
	char	c[6];

	c[0] = ' ';
	c[1] = '\t';
	c[2] = '\b';
	c[3] = '\f';
	c[4] = '\r';
	c[5] = '\0';
	if (!str)
		return (NULL);
	splited = ft_split(str, c);
	if (!splited)
		return (NULL);
	size = calc_clean_size(splited);
	cleaned = malloc(sizeof(char) * (size + 1));
	if (!cleaned)
		return (free_memory(splited), NULL);
	copy_cleaned(splited, cleaned);
	free_memory(splited);
	return (cleaned);
}
