/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:19:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/03 16:55:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				parse_async(t_token **token, t_p_param *param, t_s_env *e)
{
	(*param->list)->async = 1;
	return (parse_list(token, param, e));
}
