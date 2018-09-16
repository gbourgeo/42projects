/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_newlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 21:40:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/28 21:42:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_lib		*ps_newlist(int c)
{
	t_lib		*num;

	if ((num = (t_lib*)malloc(sizeof(*num))) == NULL)
		return (NULL);
	num->nb = c;
	num->next = NULL;
	return (num);
}
