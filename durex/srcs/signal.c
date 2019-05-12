/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 17:30:40 by root              #+#    #+#             */
/*   Updated: 2019/05/12 16:48:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "main.h"

void		durexSigterm(int sig)
{
	if (sig != SIGTERM)
		return ;
	serverLog(1, "[LOGS] - Signal received %d\n", sig);
	quitClearlyServer();
	quitClearlyDaemon();
	exit(0);
}
