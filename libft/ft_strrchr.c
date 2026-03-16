/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:52:38 by hgutterr          #+#    #+#             */
/*   Updated: 2025/04/09 11:52:39 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (char ) c)
			last = s;
		s++;
	}
	if ((char) c == '\0')
		return ((char *) s);
	return ((char *) last);
}

/* int	main()
{
	char *s = "HELLO";
	char *res = ft_strrchr(s, 'L');
	printf("%s\n", res);
} */
