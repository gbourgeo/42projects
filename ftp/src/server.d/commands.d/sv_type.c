/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 22:41:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/18 20:26:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

typedef struct		s_type
{
	char		name;
	int			value;
	int			more_arg;
}					t_type;

static int			sv_second_type(char *type, char *value, t_client *cl)
{
	static t_type	second_arg[] = {
		{ 'N', data_type_non_print, 0 }, { 'T', data_type_telnet, 0 },
		{ 'C', data_type_asa, 0 },
	};
	size_t			i;

	i = 0;
	if (!value)
		return (ERR_NB_PARAMS);
	if (type[0] == 'L')
	{
		cl->data.byte_size = ft_atoi(value);
		return (IS_OK);
	}
	if (ft_strlen(value) == 1)
		while (i < sizeof(second_arg) / sizeof(second_arg[0]))
		{
			if (value[0] == second_arg[i].name)
			{
				cl->data.type |= (1 << second_arg[i].value);
				return (IS_OK);
			}
			i++;
		}
	return (ERR_WRONG_PARAM);
}

int					sv_type(char **cmds, t_client *cl, t_server *sv)
{
	static t_type	first_arg[] = {
		{ 'A', data_type_ascii, 1 }, { 'E', data_type_ebcdic, 1 },
		{ 'I', data_type_image, 0 }, { 'L', data_type_byte_size, 1 },
	};
	size_t			i;

	i = 0;
	if (!cmds[1])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (ft_strlen(cmds[1]) == 1)
		while (i < sizeof(first_arg) / sizeof(first_arg[0]))
		{
			if (cmds[1][0] == first_arg[i].name)
			{
				cl->data.type = 0;
				cl->data.type |= (1 << first_arg[i].value);
				if (first_arg[i].more_arg)
					if ((i = sv_second_type(cmds[1], cmds[2], cl)) != IS_OK)
						return (sv_cmd_err(ft_get_error(i), cmds[0], cl, sv));
				return (sv_cmd_ok("Data type replaced.", cl, sv));
			}
			i++;
		}
	return (sv_cmd_err(ft_get_error(ERR_WRONG_PARAM), cmds[0], cl, sv));
}

int				sv_type_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Type of transfert\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
