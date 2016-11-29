/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 18:32:33 by root              #+#    #+#             */
/*   Updated: 2016/10/23 19:08:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	catch_sig(int sig)
{
	printf("\nsignal caught: %d\n", sig);
	/* clear(); */
	/* clear(); */
	/* clear(); */
	exit(1);
}

void		ft_signal(t_env *e)
{
	if (signal(SIGINT, catch_sig) < SIG_ERR)
		ft_err("signal", e);
}
