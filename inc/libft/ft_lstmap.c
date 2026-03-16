/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:29:59 by hgutterr          #+#    #+#             */
/*   Updated: 2025/04/17 15:30:00 by hgutterr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_object;

	if (!lst | !f | !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_object = ft_lstnew(f(lst->content));
		if (!new_object)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_object);
		lst = lst->next;
	}
	return (new_list);
}
