/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 11:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/02 18:34:28 by gbourgeo         ###   ########.fr       */
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
** The maximum lenght a client can be named.
*/

# define NAME_SIZE	9

/*
** All commands the server supports, and their associated function.
*/

# define COMMANDS1 "/away", "/connect", "/help", "/join", "/leave", "/list"
# define COMMANDS2 "/msg", "/nick", "/quit", "/topic", "/who", NULL

# define SYNTAX1 "<message>", "<_host> <port>", "<command>", "<channel>"
# define SYNTAX2 "<channel>", "", "<nicknames> <message>", "<nickname>"
# define SYNTAX3 "[<comment>]", "<channel> [<topic>]", "<channel>", NULL

# define END_CHECK "\r\n"
# define END_CHECK_LEN 2

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
