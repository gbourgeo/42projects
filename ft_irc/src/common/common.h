/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 11:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 04:07:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"

/*
** The size of this server / client Ringbuffer on read and write.
*/

# define BUFF		512

/*
** The maximum lenght a nickname can be.
*/

# define NICK_LEN	9

/*
** Default port number
*/

# define DEF_PORT	"6667"

/*
** All commands the server supports, and their associated function.
*/

# define COMMANDS1 "AWAY", "CONNECT", "HELP", "JOIN", "LEAVE", "LIST"
# define COMMANDS2 "MSG", "NICK", "QUIT", "TOPIC", "WHO", NULL

# define SYNTAX1 "<message>", "<_host> <port>", "<command>", "<channel>"
# define SYNTAX2 "<channel>", "", "<nicknames> <message>", "<nickname>"
# define SYNTAX3 "[<comment>]", "<channel> [<topic>]", "<channel>", NULL

# define END_CHECK "\r\n"
# define END_CHECK_LEN 2

# define ISSPECIAL(c) (((c) >= '[' && (c) <= '`') || ((c) >= '{' && (c) <= '}'))

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
	int					len;
}						t_buf;

void					ft_free(char ***cmds);

#endif
