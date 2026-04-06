/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:49:52 by myivanov          #+#    #+#             */
/*   Updated: 2026/04/06 15:09:03 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include "../inc/libft/libft.h"

int	f_c_type(char *str)
{
	if (!ft_strncmp(str, "./", 2))
		return (2); //file type
	else
		return (1); //RGB type
}

int	is_numeric_str(char *str)
{
	int	j;

	j = 0;
	if (!str || !str[0])
		return (0);
	while (str[j])
	{
		if (!(str[j] >= '0' && str[j] <= '9'))
			return (0);
		j++;
	}
	return (1);
}

int	validate_rgb_values(char **splited)
{
	int	i;
	int	result;

	i = 0;
	while (splited[i])
	{
		if (!is_numeric_str(splited[i]))
			return (0);
		result = ft_atoi(splited[i]);
		if (result < 0 || result > 255)
			return (0);
		i++;
	}
	return (1);
}