/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:24:46 by hgutterr          #+#    #+#             */
/*   Updated: 2025/04/14 15:24:47 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_separator(char a, char c)
{
	return (a == c);
}

static int	ft_wordcount(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (!is_separator(s[i], c))
		{
			words++;
			while (s[i] != '\0' && !is_separator(s[i], c))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	*ft_splitter(char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] != '\0' && (!is_separator(s[i], c)))
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && !is_separator(s[i], c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**str_splitted;
	char	*s_ptr;
	int		i;
	int		j;

	s_ptr = (char *)s;
	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	str_splitted = ft_calloc((ft_wordcount(s_ptr, c) + 1), sizeof(char *));
	if (!str_splitted)
		return (NULL);
	while (s_ptr[i] != '\0')
	{
		if (!is_separator(s_ptr[i], c))
		{
			str_splitted[j++] = ft_splitter(&s_ptr[i], c);
			while (s_ptr[i] != '\0' && !is_separator(s_ptr[i], c))
				i++;
		}
		else
			i++;
	}
	return (str_splitted);
}
