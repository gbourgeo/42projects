/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:57:14 by beborch           #+#    #+#             */
/*   Updated: 2017/12/02 02:13:27 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (!(*alst))
		return ;
	if (!((*alst)->content))
	{
		del((*alst)->content, (*alst)->content_size);
	}
	free(*alst);
	*alst = NULL;
	return ;
}
