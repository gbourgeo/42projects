/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 22:41:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:26:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include "sv_struct.h"

static t_type		*sv_firsttype(char type)
{
	static t_type	firsttype[] = {
		{ 'A', data_type_ascii, sv_type_ae },
		{ 'E', data_type_ebcdic, sv_type_ae },
		{ 'I', data_type_image, sv_type_i },
		{ 'L', data_type_byte_size, sv_type_l },
	};
	long			i;

	i = sizeof(firsttype) / sizeof(firsttype[0]);
	while (--i >= 0)
		if (firsttype[i].name == type || firsttype[i].name + 32 == type)
			return (firsttype + i);
	return (NULL);
}

/*
** TYPE
** 200
** 500, 501, 504, 421, 530
*/

int					sv_type(char **cmds, t_client *cl)
{
	t_type		*type;
	int			errnb;

	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cmds[1] || !cmds[1][0])
		return (sv_response(cl, "501 %s", ft_get_error(ERR_NB_PARAMS)));
	errnb = ERR_INVALID_PARAM;
	if (ft_strlen(cmds[1]) == 1 && (type = sv_firsttype(cmds[1][0])))
		if ((errnb = type->handler(cmds[2], cl)) == IS_OK)
		{
			cl->data.type |= (1 << type->value);
			return (sv_response(cl, "200 type set to %s", cmds[1]));
		}
	return (sv_response(cl, "501 %s", ft_get_error(errnb)));
}

/*
** TYPE <SP> <type-code> <CRLF>
*/

int					sv_type_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"The argument specifies the representation type as described",
		"in the Section on Data Representation and Storage.  Several",
		"types take a second parameter.  The first parameter is",
		"denoted by a single Telnet character, as is the second",
		"Format parameter for ASCII and EBCDIC; the second parameter",
		"for local byte is a decimal integer to indicate Bytesize.",
		"The parameters are separated by a <SP> (Space, ASCII code 32).", "",
		"The following codes are assigned for type:", "",
		"		  \\    /",
		"	A - ASCII |    | N - Non-print",
		"		  |-><-| T - Telnet format effectors",
		"	E - EBCDIC|    | C - Carriage Control (ASA)",
		"		  /    \\",
		"	I - Image", "",
		"	L <byte size> - Local byte Byte size", "",
		"The default representation type is ASCII Non-print.  If the",
		"Format parameter is changed, and later just the first",
		"argument is changed, Format then returns to the Non-print",
		"default.", NULL
	};

	return (sv_print_help(cl, cmd, "<type-code>", help));
}
