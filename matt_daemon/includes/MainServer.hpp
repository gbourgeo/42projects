// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MainServer.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/25 07:35:36 by root              #+#    #+#             //
//   Updated: 2017/09/28 00:14:17 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAINSERVER_HPP
# define MAINSERVER_HPP

# include "Tintin.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"
# include <signal.h>

# define LOCK_FILE	"/var/lock/matt_daemon.lock"

Tintin_reporter	*tintin = NULL;
Server			*server = NULL;

void			quitClearlyDaemon(const char *info, std::string more, bool unlock);
void			daemonize(void);
void			daemonSigHandler(int sig);

#endif
