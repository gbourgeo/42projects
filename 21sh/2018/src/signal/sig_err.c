/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:41:03 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 09:45:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "siglist.h"
#include "signal_intern.h"

char	*sig_err_translate(int sig)
{
	static char		*tab[] = {
		0, SGHUP, SINT, SQUIT, SILL, STRAP, SABRT, SEMT, SFPE, SKILL,
		SBUS, SSEGV, SSYS, SPIPE, SALRM, STERM, SURG, SSTOP, STSTP, SCONT,
		SCHLD, STTIN, STTOU, SIO, SXCPU, SXFSZ, SVTALRM, SPROF, SWINCH, SLOST,
		SUSR1, SUSR2,
	};

	return (tab[sig]);
}
