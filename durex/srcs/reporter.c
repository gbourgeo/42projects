/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 22:47:39 by root              #+#    #+#             */
/*   Updated: 2019/08/06 00:36:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* mutex */
#include <pthread.h>

#include "main.h"

int				hireReporter(void)
{
	e.server.reporter = open(SERVER_REPORTER, O_CREAT | O_TRUNC | O_RDWR, 0600);
	pthread_mutex_init(&e.server.mutex, NULL);
	return e.server.reporter >= 0;
}
