/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/29 15:33:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/04/29 18:25:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void			ft_script_error(char *str, char *str2, int fd)
{
	ft_putstr_fd("ft_script: ", fd);
	ft_putstr_fd(str, fd);
	ft_putendl_fd(str2, fd);
	ft_putstr_fd("ft_script: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(str2, 2);
}
