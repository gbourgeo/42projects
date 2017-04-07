/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_users_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 08:48:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <fcntl.h>

static void			sv_connection_class(char **table, t_env *e)
{
	ft_puttab(table);
	(void)e;
}

static void			sv_client_connection(char **table, t_env *e)
{
	t_user			*ptr;

	if (ft_tablen(table) < 5)
		return ;
	if ((ptr = malloc(sizeof(*ptr))) == NULL)
		sv_error("Malloc (t_user) failed.", e);
	ft_memset(ptr, 0, sizeof(*ptr));
	ft_strncpy(ptr->hostaddr, *table++, ADDR_LEN);
	if (**table)
		ptr->passwd = ft_strdup(*table);
	table++;
	ft_strncpy(ptr->hostname, *table++, NI_MAXHOST);
	table++;
	ptr->class = ft_atoi(*table);
	ptr->next = (ptr->passwd) ? e->conf.pass_user : e->conf.allowed_user;
	if (ptr->passwd)
		e->conf.pass_user = ptr;
	else
		e->conf.allowed_user = ptr;
}

static void			sv_operator_privilege(char **table, t_env *e)
{
	t_user			*ptr;

	if (ft_tablen(table) < 5)
		return ;
	if ((ptr = malloc(sizeof(*ptr))) == NULL)
		sv_error("Malloc (t_file) failed.", e);
	ft_memset(ptr, 0, sizeof(*ptr));
	ft_strncpy(ptr->hostname, *table++, ADDR_LEN);
	if (**table)
		ptr->passwd = ft_strdup(*table);
	table++;
	ft_strncpy(ptr->nick, *table++, NICK_LEN);
	table++;
	ptr->class = ft_atoi(*table);
	ptr->next = e->conf.opers;
	e->conf.opers = ptr;
}

static int			sv_pos(char *line, char **table)
{
	char			*ptr;

	ptr = line;
	while (ptr && *ptr)
	{
		if (*ptr == **table)
			return (ptr - line);
		ptr++;
	}
	return (-1);
}

void				get_conf_file(t_env *e)
{
	int				fd;
	char			*buf;
	char			**table;
	static void		(*conf[])() = { Y_LINES, I_LINES, O_LINES };

	if ((fd = open(CONF_FILE, O_RDONLY, 0644)) < 0)
		return ;
	buf = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		table = NULL;
		if (*buf && *buf != '#' && (table = sv_strsplit(buf, ':')))
		{
			if (sv_pos(CONF_LINES, table) >= 0)
				conf[sv_pos(CONF_LINES, table)](table + 1, e);
		}
		ft_free(&table);
		free(buf);
		buf = NULL;
	}
	close(fd);
}
