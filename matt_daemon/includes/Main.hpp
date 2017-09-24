// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/23 04:40:11 by root              #+#    #+#             //
//   Updated: 2017/09/24 10:12:07 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

# include "Tintin.hpp"
# include "Server.hpp"
# include "Exceptions.hpp"
# include <signal.h>

# define LOCK_FILE	"/var/lock/matt_daemon.lock"

void			daemonize(int lock);
void			daemonSigHandler(int sig);

#endif
