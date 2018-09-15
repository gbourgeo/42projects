/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 04:06:56 by beborch           #+#    #+#             */
/*   Updated: 2017/12/02 06:11:51 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst;
	t_list *tmp;

	lst = *alst;
	while (lst)
	{
		if (lst->content)
			del(lst->content, lst->content_size);
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
	*alst = NULL;
}
