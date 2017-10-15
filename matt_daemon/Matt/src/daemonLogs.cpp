// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   daemonLogs.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:27:18 by root              #+#    #+#             //
//   Updated: 2017/10/15 18:30:00 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "daemonLogs.hpp"

void		Server::sendDaemonLogs(t_client &cl)
{
	std::ifstream	log(LOG_FILE, std::ifstream::binary);
	int				len;
	char			*buf;

	if (log) {
		log.seekg(0, log.end);
		len = log.tellg();
		log.seekg(0, log.beg);
		buf = new char [len];
		log.read(buf, len);
		if (log)
			write(cl.fd, buf, len);
		else {
			write(cl.fd, buf, len);
			write(cl.fd, "\nERROR: only a part of the file could be read.", 47);
		}
		log.close();
		delete buf;
	}
	else
		write(cl.fd, "Couldn't open log file.", 23);
}
