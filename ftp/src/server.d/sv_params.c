/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:02:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 18:41:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

t_opt			*sv_params(int getsize)
{
	static t_opt	opts[] = {
		{ '4', NULL, NULL, "Allows IpV4 only.", sv_param_four },
		{ '6', NULL, NULL, "Allows IpV6 only.", sv_param_six },
		{ 'd', NULL, NULL, "Users directory created (with -u).", sv_param_d },
		{ 'h', "-help", NULL, "Print help and exit.", sv_param_h },
		{ 'i', NULL, NULL, "Interactive server.", sv_param_i },
		{ 'p', "-path", "[path]", "Working path.", sv_param_p },
		{ 'u', "-user", NULL, "Registered users mode.", sv_param_u },
	};

	if (getsize)
		return (t_opt *)(sizeof(opts) / sizeof(opts[0]));
	return (opts);
}
