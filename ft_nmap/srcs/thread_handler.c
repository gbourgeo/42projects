/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 03:52:59 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/19 01:48:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_thread_handler		*add_thread_handler(t_thread_handler *threads, t_thread_handler* new)
{
	t_thread_handler *start = threads;

	if (!threads)
		return (threads);
	while (threads->next)
		threads = threads->next;
	threads->next = new;
	return (start);
}
