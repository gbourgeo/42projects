// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   daemonInfo.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:30:33 by root              #+#    #+#             //
//   Updated: 2017/10/22 14:47:14 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "daemonInfo.hpp"

std::string				Server::getDaemonInfo( void )
{
	std::string			info;
	static const char	*cmds[]	= SERV_CMDS;

	info = "Daemon written by GBOURGEO for 42.";
	info += "\n";
	info += "Daemon started on ";
	info += ctime(&this->start_time);
	info += "Daemon max. clients:  " + std::to_string(SERV_CLIENTS) + "\n";
	info += "Daemon curr. clients:  " + std::to_string(this->nb_clients) + "\n";
	info += "Daemon encrypted version : ";
	info += (SERV_ENCRYPT) ? "Yes" : "No";
	info += "\n";
	info += "Daemon passwd protected : ";
	info += (SERV_PROTECT) ? "Yes" : "No";
	info += "\n";
	info += "Daemon commands avail. :  ";
	for (int i = 0; cmds[i]; i++) {
		info += "\"";
		info += cmds[i];
		info += '"';
		info += (cmds[i + 1]) ? ", " : ".";
	}
	info += "\n";
	return info;
}

void		Server::sendDaemonInfo(t_client &cl)
{
	std::string			info = getDaemonInfo();

	write(cl.fd, &info[0], info.size());
}
