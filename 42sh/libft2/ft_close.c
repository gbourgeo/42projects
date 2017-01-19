/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 03:14:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/26 03:21:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int			ft_close(int fd)
{
	int		ret;

	if ((ret = close(fd)) == -1)
		ft_putendl_fd("42sh: Close Error.", 2);
	return (ret);
}
