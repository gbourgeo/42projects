/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_type_hdlr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 14:56:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 15:19:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include "sv_struct.h"

static t_type	*sv_secondtype(char type)
{
	static t_type	secondtype[] = {
		{ 'N', data_type_non_print, NULL }, { 'T', data_type_telnet, NULL },
		{ 'C', data_type_asa, NULL },
	};
	long			i;

	i = sizeof(secondtype) / sizeof(secondtype[0]);
	while (--i >= 0)
		if (secondtype[i].name == type || secondtype[i].name + 32 == type)
			return (secondtype + i);
	return (NULL);
}

int				sv_type_ae(char *value, t_client *cl)
{
	t_type		*second;

	if (!value || !*value)
	{
		cl->data.type |= (1 << data_type_non_print);
		return (IS_OK);
	}
	if (ft_strlen(value) == 1 && (second = sv_secondtype(value[0])))
	{
		cl->data.type |= (1 << second->value);
		return (IS_OK);
	}
	return (ERR_WRONG_PARAM);
}

int				sv_type_l(char *value, t_client *cl)
{
	if (!value || !*value || !sv_validnumber(&value, 1))
		return (ERR_WRONG_PARAM);
	cl->data.byte_size = ft_atoi(value);
	return (IS_OK);
}
