/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:11:42 by root              #+#    #+#             */
/*   Updated: 2018/04/11 03:12:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SNPRINTF_H
# define FT_SNPRINTF_H

#include "ft_base_printf.h"

int			ft_snprintf(char *str, size_t size, const char *restrict format, ...);
void		ft_snprintf_write(t_dt *data);

#endif
