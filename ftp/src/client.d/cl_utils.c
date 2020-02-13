/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:52:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 21:54:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				is_valid_response(char res[])
{
	return (ft_isdigit(res[0]) && ft_isdigit(res[1]) && ft_isdigit(res[2])
	&& res[3] == ' ');
}
