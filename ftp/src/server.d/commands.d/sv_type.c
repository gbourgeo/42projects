/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 22:41:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 18:33:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

typedef struct		s_type
{
	char		name;
	int			value;
	int			more_arg;
}					t_type;

static t_type		*sv_firsttype(char type)
{
	static t_type	firsttype[] = {
		{ 'A', data_type_ascii, 1 }, { 'E', data_type_ebcdic, 1 },
		{ 'I', data_type_image, 0 }, { 'L', data_type_byte_size, 1 },
	};
	long			i;

	i = sizeof(firsttype) / sizeof(firsttype[0]);
	while (--i >= 0)
		if (firsttype[i].name == type)
			return (firsttype + i);
	return (NULL);
}

static t_type		*sv_secondtype(char type)
{
	static t_type	secondtype[] = {
		{ 'N', data_type_non_print, 0 }, { 'T', data_type_telnet, 0 },
		{ 'C', data_type_asa, 0 },
	};
	long			i;

	i = sizeof(secondtype) / sizeof(secondtype[0]);
	while (--i >= 0)
		if (secondtype[i].name == type)
			return (secondtype + i);
	return (NULL);
}

static int			sv_type_next(t_type *type, char *value, t_client *cl)
{
	t_type		*second;

	if (type->name == 'L')
	{
		if (!value || !*value)
			return (ERR_WRONG_PARAM);
		cl->data.byte_size = ft_atoi(value);
		return (IS_OK);
	}
	if (!value || !*value)
	{
		cl->data.type |= (1 << data_type_non_print);
		return (IS_OK);
	}
	if (ft_strlen(value) == 1 && (second = sv_secondtype(value[0])))
	{
		cl->data.type |= (1 << second->value);
		return (IS_OK);
	}
	return (ERR_WRONG_PARAM);
}

int					sv_type(char **cmds, t_client *cl, t_server *sv)
{
	t_type		*type;
	int			errnb;

	if (!cmds[1])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	errnb = ERR_WRONG_PARAM;
	if (ft_strlen(cmds[1]) == 1 && (type = sv_firsttype(cmds[1][0])))
	{
		cl->data.type = 0;
		cl->data.type |= (1 << type->value);
		if (type->more_arg)
			if ((errnb = sv_type_next(type, cmds[2], cl)) == IS_OK)
				return (sv_cmd_ok("Data type replaced.", cl, sv));
	}
	return (sv_cmd_err(ft_get_error(errnb), cmds[0], cl, sv));
}

int					sv_type_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Type of transfert\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
