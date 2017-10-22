// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   daemonLogs.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:27:18 by root              #+#    #+#             //
//   Updated: 2017/10/22 14:33:52 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "daemonLogs.hpp"

std::string			Server::getDaemonLogs( void )
{
	std::ifstream	log(LOG_FILE, std::ifstream::binary);
	int				len;
	char			*buf;
	std::string		info;

	if (log) {
		log.seekg(0, log.end);
		len = log.tellg();
		log.seekg(0, log.beg);
		buf = new char [len];
		log.read(buf, len);
		info = std::string(buf);
		if (!log)
			info += "\nERROR: only a part of the file could be read.";
		log.close();
		delete[] buf;
	}
	else
		info = "Couldn't open log file.";
	info += "\n";
	return info;
}

void				Server::sendDaemonLogs(t_client &cl)
{
	std::string		logs = getDaemonLogs();

	write(cl.fd, &logs[0], logs.size());
}
