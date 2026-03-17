/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myivanov <myivanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:58:40 by hgutterr          #+#    #+#             */
/*   Updated: 2026/03/17 16:29:05 by myivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isempty(const char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t'
		|| line[i] == '\n' || line[i] == '\r'
		|| line[i] == '\v' || line[i] == '\f')
		i++;
	return (line[i] == '\0');
}
