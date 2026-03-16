/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:25:56 by hgutterr          #+#    #+#             */
/*   Updated: 2025/04/14 13:25:59 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		n;
	int		m;

	n = 0;
	if (!s1)
		return (NULL);
	while (s1[n])
	{
		if (!ft_strchr(set, s1[n]))
			break ;
		n++;
	}
	m = ft_strlen(s1) - 1;
	while (m > n)
	{
		if (!ft_strchr(set, s1[m]))
			break ;
		m--;
	}
	newstr = ft_substr(s1, n, m - n + 1);
	if (!newstr)
		return (NULL);
	return (newstr);
}
