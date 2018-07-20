/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 17:30:40 by root              #+#    #+#             */
/*   Updated: 2018/07/20 17:42:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "main.h"

void		durexSigterm(int sig)
{
	if (sig != SIGTERM)
		return ;
	quitClearlyServer();
	quitClearlyDaemon();
}
