/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 08:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/26 08:58:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "main.h"

static void		ft_sigint(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		prompt(&e);
	}
}

void			ft_signals(void)
{
	signal(SIGINT, &ft_sigint);
}
