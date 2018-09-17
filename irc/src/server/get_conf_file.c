/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_users_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 23:04:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/17 15:02:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <fcntl.h>

static void			sv_machine_information(char **table, t_env *e)
{
	if (ft_tablen(table) < 5)
		return ;
	table++;
	ft_strncpy(e->name, *table++, SERVER_LEN);
	ft_strncpy(e->addr, *table++, ADDR_LEN);
	if (!*e->addr)
		ft_strncpy(e->addr, "127.0.0.1", SERVER_LEN);
	table++;
	table++;
	ft_strncpy(e->sid, *table++, SID_LEN);
}

static void			sv_client_connection(char **table, t_env *e)
{
	t_user			*ptr;

	if (ft_tablen(table) < 6)
		return ;
	if ((ptr = malloc(sizeof(*ptr))) == NULL)
		sv_error("Malloc (t_user) failed.", e);
	ft_memset(ptr, 0, sizeof(*ptr));
	ptr->mode = **table++;
	ft_strncpy(ptr->hostaddr, *table++, ADDR_LEN);
	if (**table)
		ptr->passwd = ft_strdup(*table);
	table++;
	ft_strncpy(ptr->hostname, *table++, NI_MAXHOST);
	ft_strncpy(ptr->port, *table++, 5);
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

	if (ft_tablen(table) < 6)
		return ;
	if ((ptr = malloc(sizeof(*ptr))) == NULL)
		sv_error("Malloc (t_file) failed.", e);
	ft_memset(ptr, 0, sizeof(*ptr));
	ptr->mode = **table++;
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

static void			get_conf_lines(char *buf, t_env *e)
{
	static void		(*conf[])() = { ALL_LINES };
	char			*ptr;
	char			**table;

	ptr = sv_strchr(AVAILABLE_LINES, *buf);
	if (ptr)
	{
		table = sv_strsplit(buf, ':');
		if (table)
		{
			conf[ptr - AVAILABLE_LINES](table, e);
			ft_free(&table);
		}
	}
}

void				get_conf_file(t_env *e)
{
	int				fd;
	char			*buf;

	if ((fd = open(CONF_FILE, O_RDONLY, 0644)) < 0)
		return ;
	buf = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		if (buf)
		{
			get_conf_lines(buf, e);
			free(buf);
			buf = NULL;
		}
	}
	close(fd);
	if (!*e->name)
		gethostname(e->name, SERVER_LEN);
}
