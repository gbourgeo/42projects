// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/25 07:35:36 by root              #+#    #+#             //
//   Updated: 2017/11/18 22:03:45 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

# include "Tintin.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"
# include <signal.h>

# define LOCK_FILE	"/var/lock/matt_daemon.lock"

typedef struct		s_env
{
	Tintin_reporter	*tintin;
	Server			*server;
	int				lock;
	bool			child;
}					t_env;

struct s_env		e;

void				quitClearlyDaemon(const char *info, std::string more);
void				daemonize();
void				daemonSigHandler(int sig);

#endif
