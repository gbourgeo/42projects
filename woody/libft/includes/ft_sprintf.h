/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 03:10:40 by root              #+#    #+#             */
/*   Updated: 2018/04/11 03:13:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

#include "ft_base_printf.h"

int			ft_sprintf(char *str, const char *restrict format, ...);
void		ft_sprintf_write(t_dt *data);

#endif
