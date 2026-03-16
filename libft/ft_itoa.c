/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:02:18 by hgutterr          #+#    #+#             */
/*   Updated: 2025/04/14 16:02:22 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_check_special(int n)
{
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	return (NULL);
}

static int	len_itoa(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*newstr;
	int		len;
	int		sign;

	len = 0;
	sign = 1;
	newstr = ft_check_special(n);
	if (n < 0 && ++len)
	{
		n *= -1;
		sign = -1;
	}
	len += len_itoa(n);
	if (!newstr)
		newstr = ft_calloc(len + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	if (sign == -1)
		newstr[0] = '-';
	while (n > 0)
	{
		newstr[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (newstr);
}

/* int	main(void)
{
	printf("%s\n", ft_itoa(0));
} */
