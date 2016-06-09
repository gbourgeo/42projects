/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 04:10:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 12:45:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int					ft_new_term_attr(t_env *e)
{
	struct termios	new;

	if (ioctl(0, TIOCGETA, &e->term) == -1)
		return (ft_error(0, "Unable to get terminal attributes.", e));
	new = e->term;
	new.c_lflag &= ~(ECHO | ISIG | ICANON | ECHONL);
	new.c_cc[VMIN] = 0;
	new.c_cc[VTIME] = 30;
	if (ioctl(0, TIOCSETA, &new) == -1)
	{
		ft_error(0, "Unable to set terminal new attributes", e);
		ft_restore_term_attr(e);
		return (1);
	}
	return (0);
}

int					ft_restore_term_attr(t_env *e)
{
	int				ret;

	ret = 0;
	if (ioctl(0, TIOCSETA, &e->term) == -1)
		ret = ft_error(0, "Can't restore old term attributes", e);
	return (ret);
}
