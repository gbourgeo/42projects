// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Daemonize.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/08 13:16:37 by root              #+#    #+#             //
//   Updated: 2017/10/08 13:17:48 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DAEMONIZE_HPP
# define DAEMONIZE_HPP

# include "Exceptions.hpp"
# include <stdlib.h> //close exit
# include <unistd.h> //fork
# include <sys/types.h> //umask
# include <sys/stat.h>
# include <fcntl.h> //open
# include <signal.h>

void		quitClearlyDaemon(const char *info, std::string more);
void		daemonSigHandler(int sig);

#endif
