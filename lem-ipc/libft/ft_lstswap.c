/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 08:58:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/19 17:34:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstswap(t_list *one, t_list *two)
{
	void	*cnt;
	size_t	siz;

	cnt = one->content;
	siz = one->content_size;
	one->content = two->content;
	one->content_size = two->content_size;
	two->content = cnt;
	two->content_size = siz;
}
