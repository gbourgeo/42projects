/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:17:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/05 03:19:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONV_CHAR '%'

typedef struct  s_dt
{
    int         ret;
    char        *buff;
}				t_dt;

int				ft_printf(const char * restrict format, ...);

#endif
