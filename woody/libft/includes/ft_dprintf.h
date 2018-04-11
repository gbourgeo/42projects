/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:24:36 by root              #+#    #+#             */
/*   Updated: 2018/04/11 02:39:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

#include "ft_base_printf.h"

int			ft_dprintf(int fd, const char *restrict format, ...);
void		ft_dprintf_write(t_dt *data);

#endif
