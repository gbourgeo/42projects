/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 22:09:01 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 03:54:05 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"
#include "asm.h"

static void		err_user(t_data *d)
{
	int len;

	if ((len = ft_strlen(d->e->fd_user)) > 128)
	{
		free(d->e->fd_user);
		ft_dprintf(2, "File name too big ...");
		ft_dprintf(2, " Why would you create a file this big ? %d\n", len);
		exit(1);
	}
}

int				user_file(t_data *d)
{
	int		len;
	char	*b_name;

	err_user(d);
	d->file_name = ft_strdup(d->e->fd_user);
	if (d->e->flag & FLAG_F)
	{
		handle_dotdot(d);
		len = ft_strlen(d->file_name);
		if (d->file_name[len - 1] != '/')
			d->file_name = ft_strjoinfree(d->file_name, "/", 1);
		b_name = cut_path(basename(d->e->fd_name));
		d->file_name = ft_strjoinfree(d->file_name, b_name, 3);
	}
	else
		d->file_name = ft_strjoinfree(d->file_name, ".cor", 1);
	free(d->e->fd_user);
	if ((d->fd = open(d->file_name, O_CREAT | O_TRUNC | O_RDWR, 0700)) < 0)
		return (ERR_OPEN);
	return (0);
}

int				get_user_entry(t_env *e, char **av, int i)
{
	if (e->flag & FLAG_S || e->flag & FLAG_F)
	{
		if (av[i][0] == '\0')
		{
			ft_dprintf(2, "Ouch, you forgot your file name. ");
			ft_dprintf(2, "We could have seg fault !\n");
			exit(1);
		}
		e->fd_user = ft_strdup(av[i]);
		return (i + 1);
	}
	return (i);
}
