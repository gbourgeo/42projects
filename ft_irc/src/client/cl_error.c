/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 05:12:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/25 21:32:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int			cl_error(const char *err, t_client *cl)
{
	write(2, "\e[31m", 5);
	ft_putstr_fd(err, 2);
	write(2, "\e[0m\n", 5);
	if (cl != NULL)
		cl_quit(NULL, cl);
	return (1);
}
