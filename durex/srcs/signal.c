/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 17:30:40 by root              #+#    #+#             */
/*   Updated: 2019/08/04 05:03:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "main.h"

void		durexSigHandler(int sig)
{
	serverLog(1, "[LOGS] - Signal received %d\n", sig);
	if (sig != SIGTERM)
		return ;
	quitClearlyServer();
	quitClearlyDaemon();
	exit(0);
}
