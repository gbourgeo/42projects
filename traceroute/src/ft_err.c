/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 17:03:28 by root              #+#    #+#             */
/*   Updated: 2016/09/28 13:47:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
#include <stdio.h>

void				ft_err(char *msg, char *err_msg)
{
	fprintf(stderr, "%s: ", msg);
	if (err_msg)
		fprintf(stderr, "%s\n", err_msg);
	else
		perror("");
	if (e.outpack != NULL)
		free(e.outpack);
	if (e.probes != NULL)
		free(e.probes);
	ft_bzero(&e, sizeof(e));
	exit(2);
}
