/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 22:19:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 09:56:02 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				parse_async(t_token **token, t_p_param *param, t_s_env *e)
{
	(*param->list)->async = 1;
	return (parse_list(token, param, e));
}
