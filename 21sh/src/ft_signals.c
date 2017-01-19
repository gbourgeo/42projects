/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 21:41:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/14 18:54:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			sig_handler(int signum)
{
	if (signum == SIGSEGV)
	{
		ft_putendl("SEGFAULT !");
		ft_exit(NULL);
	}
}

void				init_signals(void)
{
	signal(SIGSEGV, &sig_handler);
}
