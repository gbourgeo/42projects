// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   machineInfo.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:32:02 by root              #+#    #+#             //
//   Updated: 2017/10/15 18:32:20 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "machineInfo.hpp"

void		Server::sendMachineInfo(t_client & cl)
{
	std::string			info;
	struct utsname		buf;

	info = "- MACHINE INFORMATION -\n";
	if (uname(&buf) < 0) {
		info += "**ERROR**: Unable to get System Information : ";
		info += strerror(errno);
	} else {
		info += "\nOS\tName\tRelease\t\tHardware\n";
		info += "-------------------------------------------------";
		info += "-------------------------------------------------\n";
		info += buf.sysname;
		info += "\t";
		info += buf.nodename;
		info += "\t";
		info += buf.release;
		info += "\t";
		info += buf.machine;
		info += "\n";
		info += "\nVersion\n";
		info += "---------------------------------------------";
		info += "---------------------------------------------\n";
		info += buf.version;
		info += "\n";
	}
	write(cl.fd, &info[0], info.size());
}
