/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/12 04:08:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/05/15 00:31:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*ptr;

	if (!alst || !*alst)
		return ;
	ptr = *alst;
	del(ptr->content, ptr->content_size);
	ft_lstdel(&ptr->next, del);
	free(ptr);
}
