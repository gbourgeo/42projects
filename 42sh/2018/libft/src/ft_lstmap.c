/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 03:10:38 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/14 03:56:05 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*fct;
	t_list	*tmp;

	if (lst == NULL || f == NULL)
		return (NULL);
	fct = f(lst);
	if (!(new = ft_lstnew(fct->content, fct->content_size)))
		return (NULL);
	tmp = new;
	lst = lst->next;
	while (lst && f)
	{
		fct = f(lst);
		if (!(tmp->next = ft_lstnew(fct->content, fct->content_size)))
			return (NULL);
		tmp = tmp->next;
		lst = lst->next;
	}
	return (new);
}
