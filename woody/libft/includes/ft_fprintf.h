/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 00:14:23 by root              #+#    #+#             */
/*   Updated: 2018/04/11 00:54:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_H
# define FT_FPRINTF_H

# include <stdio.h>
# include "ft_base_printf.h"

int			ft_fprintf(FILE *stream, const char *restrict format, ...);
void		ft_fprintf_write(t_dt *data);

#endif
