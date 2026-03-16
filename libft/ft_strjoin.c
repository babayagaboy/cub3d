/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:56:09 by hgutterr          #+#    #+#             */
/*   Updated: 2025/04/11 23:56:10 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*s1_ptr;
	char	*s2_ptr;

	if (!s1 || !s2)
		return (NULL);
	s1_ptr = (char *)s1;
	s2_ptr = (char *)s2;
	newstr = malloc(ft_strlen(s1_ptr) + ft_strlen(s2_ptr) + 1);
	if (!newstr)
		return (NULL);
	newstr[0] = '\0';
	ft_strcat(newstr, s1_ptr);
	ft_strcat(newstr, s2_ptr);
	return (newstr);
}
