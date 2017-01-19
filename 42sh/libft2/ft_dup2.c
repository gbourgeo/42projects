/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 03:11:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/26 05:58:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft2.h"
#include <unistd.h>

int			ft_dup2(int oldd, int newd)
{
	int		ret;

	if (newd != oldd)
		ft_close(newd);
	if ((ret = dup2(oldd, newd)) == -1)
		ft_putendl_fd("42sh: Dup2 Error.", 2);
	return (ret);
}
