// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   getSocket.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 15:51:27 by root              #+#    #+#             //
//   Updated: 2017/10/15 16:46:21 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GETSOCKET_HPP
# define GETSOCKET_HPP

int			servSocket(struct addrinfo *p);
int			mailSocket(struct addrinfo *p);
int			getSocket(const char *addr, const char *port, int (*func)(addrinfo *));

#endif
