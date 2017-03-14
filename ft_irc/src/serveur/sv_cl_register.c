/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_register.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 20:23:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 06:15:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static size_t		calc_len(t_fd *cl)
{
	size_t			len;
	char			*ptr;

	len = 0;
	ptr = cl->wr.head;
	while (ptr != cl->wr.tail)
	{
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
		else
		{
			ptr++;
			len++;
		}
	}
	return (len);
}

static void			copy_str(char *str, size_t len, t_fd *cl)
{
	size_t			i;
	char			*ptr;

	i = 0;
	ptr = cl->wr.head;
	while (ptr != cl->wr.tail)
	{
		if (ptr == cl->wr.end)
			ptr = cl->wr.start;
		else
			str[i++] = *ptr++;
		if (len && i > len)
			break ;
	}
	str[i] = '\0';
}

static void			check_cl_register(t_fd *cl, t_env *e)
{
	t_file			*ptr;

	ptr = e->users;
	while (ptr)
	{
		if (!ft_strcmp(ptr->username, cl->reg.username))
		{
			if (!ft_strcmp(ptr->password, cl->reg.password))
			{
				ft_strncpy(cl->reg.nick, ptr->nick, NICK_LEN);
				sv_welcome(e, cl);
				return ;
			}
			cl->leaved = 1;
			send(cl->fd, "Invalid password.", 17, 0);
			return ;
		}
		ptr = ptr->next;
	}
	cl->leaved = 1;
	send(cl->fd, "Invalid username.", 17, 0);
}

void				sv_get_cl_password(t_fd *cl, t_env *e)
{
	size_t			len;

	len = 0;
	if (cl->reg.registered == 0)
	{
		copy_str(cl->reg.username, NICK_LEN, cl);
		send(cl->fd, "Password: ", 10, 0);
		cl->reg.registered = -2;
	}
	else
	{
		len = calc_len(cl);
		if ((cl->reg.password = ft_strnew(len + 1)) == NULL)
			sv_error("SERVER is running out of memory.\r\n", e);
		copy_str(cl->reg.password, 0, cl);
		check_cl_register(cl, e);
	}
}
