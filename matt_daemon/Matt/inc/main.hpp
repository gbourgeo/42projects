// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/25 07:35:36 by root              #+#    #+#             //
//   Updated: 2017/09/28 18:39:12 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

# include "Tintin.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"
# include <signal.h>

# define LOCK_FILE	"/var/lock/matt_daemon.lock"

Tintin_reporter	*tintin = NULL;
Server			*server = NULL;

void			quitClearlyDaemon(const char *info, std::string more, int lock, bool first);
void			daemonize(int lock);
void			daemonSigHandler(int sig);

#endif
