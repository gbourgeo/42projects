/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 18:30:37 by root              #+#    #+#             */
/*   Updated: 2016/10/23 19:05:41 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void		ft_err(char *err, t_env *e)
{
	fprintf(stderr, "%s: ", e->prog);
	perror(err);
	exit(1);
}

void		ft_err2(char *err, t_env *e)
{
	fprintf(stderr, "%s: %s\n", e->prog, err);
	exit(1);
}
