/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/17 08:50:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/19 17:30:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstaddend(t_list **alst, t_list *new)
{
	t_list	*run;

	run = *alst;
	if (run)
	{
		while (run->next)
			run = run->next;
		run->next = new;
	}
	else
		*alst = new;
}
