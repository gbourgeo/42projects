/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:16:36 by root              #+#    #+#             */
/*   Updated: 2018/07/13 00:15:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

# define DUREX_LOCK_FILE "/var/lock/durex.lock"

typedef struct	s_env
{
	int			lock;
	char		child;
}				t_env;

t_env			e;

int				durex();
void			quitClearlyDaemon();

#endif /* DUREX_H */
