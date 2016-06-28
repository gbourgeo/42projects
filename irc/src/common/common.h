/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 11:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 18:12:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"

/*
** The size of this server / client Ringbuffer on read and write.
*/

# define BUFF		256

/*
** The maximum lenght a client can be named.
*/

# define NAME_SIZE	9

/*
** The maximum lenght a channels' name. Over this value, a
** channel will not be created.
*/

# define CHAN_SIZE	50

/*
** All commands the server supports, and their associated function.
*/

# define COMMANDS1 "/nick", "/join", "/leave", "/msg", "/who", "/list", "/help"
# define COMMANDS2 "/quit", "/connect", NULL

# define SV_FUNCT1 sv_nick, sv_join, sv_leave, sv_msg, sv_who, sv_list, sv_help
# define SV_FUNCT2 sv_cl_end, sv_connect, sv_null

# define CL_FUNCT1 cl_nick, cl_void, cl_void, cl_void, cl_void, cl_void, cl_help
# define CL_FUNCT2 cl_quit, cl_connect, cl_void

# define END_CHECK "\e[31m\e[0m"
# define END_CHECK_LEN 9

/*
** Structure s_buf implemented for client write and server read / write
** circular buffer.
*/

typedef struct			s_buf
{
	char				*start;
	char				*end;
	char				*head;
	char				*tail;
}						t_buf;

void					ft_free(char ***cmds);

#endif
