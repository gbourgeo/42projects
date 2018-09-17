/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nick_change.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 18:41:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:33:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <time.h>

void			sv_nick_change(t_fd *cl, t_env *e)
{
	int			nb;
	char		name[NICK_LEN + 1];
	char		*ptr;

	if (time(NULL) - cl->inf->must_change_nick >= 30)
	{
		nb = cl->i.fd;
		ft_strncpy(name, "Guest-000", NICK_LEN + 1);
		name[NICK_LEN - 1] += (nb % 10);
		name[NICK_LEN - 2] += (nb / 10 % 10);
		name[NICK_LEN - 3] += (nb / 100 % 10);
		ptr = name;
		sv_nick(&ptr, e, cl);
	}
}
