/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 22:38:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:14:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include "cl_struct.h"

t_opt			*cl_params(int getsize)
{
	static t_opt	opt[] = {
		{ 'v', NULL, NULL, "More verbose client.", cl_param_i },
		{ 'h', "-help", NULL, "Print help and exit.", cl_param_h },
	};

	if (getsize)
		return (t_opt *)(sizeof(opt) / sizeof(opt[0]));
	return (opt);
}
