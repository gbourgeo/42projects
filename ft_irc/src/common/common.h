/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/14 11:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 20:38:56 by gbourgeo         ###   ########.fr       */
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
char					*ft_strtoupper(char *str);
char					*ft_strtolower(char *str);

#endif
