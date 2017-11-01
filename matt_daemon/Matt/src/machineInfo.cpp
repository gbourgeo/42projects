// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   machineInfo.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:32:02 by root              #+#    #+#             //
//   Updated: 2017/11/01 14:31:23 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "machineInfo.hpp"

std::string			Server::getMachineInfo( void )
{
	std::string		info;
	struct utsname	buf;

	info = "- MACHINE INFORMATION -\n";
	if (uname(&buf) < 0) {
		info += "**ERROR**: Unable to get System Information : ";
		info += strerror(errno);
	} else {
		info += "\n";
		info += "OS\tName\tRelease\t\tHardware";
		info += "\n";
		info += "-------------------------------------------------";
		info += "-------------------------------------------------";
		info += "\n";
		info += buf.sysname;
		info += "\t";
		info += buf.nodename;
		info += "\t";
		info += buf.release;
		info += "\t";
		info += buf.machine;
		info += "\n\n";
		info += "Version";
		info += "\n";
		info += "---------------------------------------------";
		info += "---------------------------------------------";
		info += "\n";
		info += buf.version;
		info += "\n";
	}
	info += "\n";
	return info;
}

void				Server::sendMachineInfo(t_client & cl)
{
	std::string		info = getMachineInfo();

	cl.wr += info;
}
