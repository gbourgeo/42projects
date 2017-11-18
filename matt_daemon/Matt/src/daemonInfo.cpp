// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   daemonInfo.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:30:33 by root              #+#    #+#             //
//   Updated: 2017/11/19 00:09:21 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "daemonInfo.hpp"
#include "stdlib_func.hpp"

std::string				Server::getDaemonInfo( void )
{
	std::string			info;
	static const char	*cmds[][100] = SERV_CMDS;

	info = "Daemon written by GBOURGEO for 42.";
	info += "\n";
	info += "Daemon started on ";
	info += ctime(&this->start_time);
	info += "Daemon max. clients:  " + std::to_string(SERV_MAX_CLIENTS) + "\n";
	info += "Daemon curr. clients:  " + std::to_string(this->nb_clients) + "\n";
	info += "Daemon encrypted version : ";
	info += (this->encrypt) ? "Yes" : "No";
	info += "\n";
	info += "Daemon passwd protected : ";
	info += (this->protect) ? "Yes" : "No";
	info += "\n";
	info += "Daemon passwd:        \"";
	info += this->passwd.c_str();
	info += "\"\n";
	info += "Daemon commands available :";
	for (int i = 0; cmds[i][0]; i++) {
		info += "\n- \"";
		info += cmds[i][0];
		info += "\"\t";
		if (mystrlen(cmds[i][0]) <= 9)
			info += "\t";
		info += cmds[i][1];
	}
	info += "\n";
	return info;
}

void		Server::sendDaemonInfo(t_client &cl)
{
	std::string			info = getDaemonInfo();

	cl.wr += info;
}
