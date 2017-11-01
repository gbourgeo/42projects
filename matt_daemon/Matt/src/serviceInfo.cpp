// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   serviceInfo.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:35:39 by root              #+#    #+#             //
//   Updated: 2017/11/01 14:11:08 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "serviceInfo.hpp"

std::string		Server::getServiceInfo( void )
{
	std::string	attr[] = { "UP", "BROADCAST", "DEBUG", "LOOPBACK", "POINTOPOINT", \
						   "RUNNING", "NOARP", "PROMISC", "NOTRAILERS", "ALLMULTI", \
						   "MASTER", "SLAVE", "MULTICAST", "PORTSEL", "AUTOMEDIA", \
						   "DYNAMIC" };
	unsigned int val[] = { IFF_UP, IFF_BROADCAST, IFF_DEBUG, IFF_LOOPBACK, IFF_POINTOPOINT, \
						   IFF_RUNNING, IFF_NOARP, IFF_PROMISC, IFF_NOTRAILERS, IFF_ALLMULTI, \
						   IFF_MASTER, IFF_SLAVE, IFF_MULTICAST, IFF_PORTSEL, IFF_AUTOMEDIA, \
						   IFF_DYNAMIC };
	struct ifaddrs		*ifstruct	= NULL;
	struct ifaddrs		*ifs		= NULL;
	void				*addr		= NULL;
	std::string			info;

	info = "- INTERFACES INFORMATION -";
	info += "\n";
	if (getifaddrs(&ifstruct) < 0) {
		info += "**ERROR*: Unable to get Interface Addresses : ";
		info += strerror(errno);
	} else {
		info += "\n";
		info += "Name\t Parameters\n";
		info += "---------------------------------------------";
		info += "---------------------------------------------";
		for (ifs = ifstruct; ifs != NULL; ifs = ifs->ifa_next) {
			if (!ifs->ifa_addr)
				continue ;
			if (ifs->ifa_addr->sa_family == AF_INET) {
				info += "\n";
				info += ifs->ifa_name;
				info += ":\t flags \t";
				info += "<";
				for (int i = 0, j = 0; i < 16; i++) {
					if (ifs->ifa_flags & val[i]) {
						if (j)
							info += ",";
						info += attr[i];
						j = 1;
					}
				}
				info += ">";

				info += "\n";
				info += "\t inet \t";
				addr = &((struct sockaddr_in *)ifs->ifa_addr)->sin_addr;
				char	buf4[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, addr, buf4, INET_ADDRSTRLEN);
				info += buf4;

				/* NOT optimal to open the file everytime, but meh.... */
				std::ifstream	inet6("/proc/net/if_inet6", std::ifstream::binary);
				if (inet6) {
					std::string	name;
					while (std::getline(inet6, name))
					{
						if (name.find(ifs->ifa_name) != std::string::npos)
						{
							info += "\n";
							info += "\t inet6 \t";
							int i = 0;
							for (int j = 0, c = 0; name[i] && name[i] != ' '; i++, j++) {
								if (j == 4) {
									i -= 4;
									int k;
									for (k = 4; k > 0; k--) {
										if (name.at(i) != '0')
											break ;
										name.erase(i, 1);
									}
									i += k;
									if (k == 0)
										c++;
									if (k != 0 || c < 2 || i < 2)
										name.insert(i++, 1, ':');
									j = 0;
								}
							}
							name.erase(i);
							info += name;
							break;
						}
					}
					inet6.close();
				}

				info += "\n";
				info += "\t netmask \t";
				addr = &((struct sockaddr_in *)ifs->ifa_netmask)->sin_addr;
				inet_ntop(AF_INET, addr, buf4, INET_ADDRSTRLEN);
				info += buf4;
				info += "\n";

				if (ifs->ifa_flags & IFF_BROADCAST) {
					info += "\t broadcast \t";
					addr = &((struct sockaddr_in *)ifs->ifa_broadaddr)->sin_addr;
					inet_ntop(AF_INET, addr, buf4, INET_ADDRSTRLEN);
					info += buf4;
					info += "\n";
				}
				if (ifs->ifa_flags & IFF_POINTOPOINT) {
					info += "\t point-to-point \t";
					addr = &((struct sockaddr_in *)ifs->ifa_dstaddr)->sin_addr;
					inet_ntop(AF_INET, addr, buf4, INET_ADDRSTRLEN);
					info += buf4;
					info += "\n";
				}

				if (ifs->ifa_data) {
					info += "\t data \t";
					info += (char *)ifs->ifa_data;
					info += "\n";
				}
			}
		}
		freeifaddrs(ifstruct);
	}
	info += "\n";
	return info;
}

void				Server::sendServiceInfo( t_client & cl )
{
	std::string		info = getServiceInfo();

	cl.wr += info;
}
