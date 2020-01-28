/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_welcome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:29:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/28 17:00:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "sv_main.h"

int			sv_welcome(t_client *cl, t_server *sv)
{
	time_t		rawtime;
	struct tm	*timeinfo;
	char		*svinfo;
	int			errnb;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	svinfo = (FT_CHECK(sv->options, sv_user_mode)) ?
	"This is a private system - No guest login" :
	"This is a public system - Guest login granted";
	if ((errnb = sv_response(cl, "220-Welcome to GBO FTP Server.")) == IS_OK
	&& (errnb = sv_response(cl, "You are user %d of %d allowed.",
	sv->connected, CLIENTS_MAX)) == IS_OK
	&& (errnb = sv_response(cl, "Local time is %d:%d. Server port: %s.",
	timeinfo->tm_hour, timeinfo->tm_min, sv->port)) == IS_OK
	&& (errnb = sv_response(cl, "%s.", svinfo)) == IS_OK)
		errnb = sv_response(cl, "220 Have Fun.");
	return (errnb);
}
