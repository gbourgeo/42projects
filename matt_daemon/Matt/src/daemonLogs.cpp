// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   daemonLogs.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:27:18 by root              #+#    #+#             //
//   Updated: 2017/11/11 22:24:28 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "daemonLogs.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

std::string			Server::getDaemonLogs( void )
{
	int				log;
	char			buff[1024];
	std::string		info;

	log = open(LOG_FILE, O_RDONLY);
	if (log != -1)
	{
		int ret;
		while ((ret = read(log, buff, 1023)) > 0) {
			info += std::string(buff, ret);
		}
		close(log);
	}
	else
		info = "Couldn't open log file.";
	info += "\n";
	return info;
}

void				Server::sendDaemonLogs(t_client &cl)
{
	std::string		logs = getDaemonLogs();

	cl.wr += logs;
}
