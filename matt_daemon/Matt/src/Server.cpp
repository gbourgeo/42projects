// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2017/10/08 12:50:06 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "Exceptions.hpp"
#include <fstream>
#include <string>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>

Server::Server(void):
	tintin(NULL),
	nb_clients(0),
	encrypt(SERV_ENCRYPT),
	protect(SERV_PROTECT)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;

	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	this->servfd = -1;
	if (getaddrinfo(SERV_ADDR, SERV_PORT, &hints, &res))
		throw DAEMONException("Unable to resolve the server address.");
	p = res;
	while (p != NULL)
	{
		if (this->servfd < 0 && p->ai_family == AF_INET)
			this->servfd = Server::findSocket(p);
		if (this->servfd != -1)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || this->servfd < 0)
	{
		errno = 0;
		throw DAEMONException("Invalid address o/ Unavailable port");
	}
	if (listen(this->servfd, SERV_CLIENTS) == -1)
		throw DAEMONException("listen");
	mymemset(&this->client[0], 0, sizeof(t_client) * SERV_CLIENTS);
	for (int i = 0; i < SERV_CLIENTS; i++) {
		this->client[i].fd = -1;
	}
	this->loop = true;
	this->start_time = time(NULL);
}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void)
{
	if (this->servfd > -1)
		close(this->servfd);
	for (int i = 0; i < SERV_CLIENTS; i++)
	{
		if (this->client[i].fd != -1)
			close(this->client[i].fd);
	}
	this->loop = false;
}

Server & Server::operator=(Server const & rhs)
{
	(void)rhs;
	return *this;
}

int			Server::findSocket(struct addrinfo *p)
{
	int		fd;
	int		on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
	{
		close(fd);
		return -1;
	}
	if (bind(fd, p->ai_addr, p->ai_addrlen) == -1)
	{
		close(fd);
		return -1;
	}
	return fd;
}

void		Server::setReporter(Tintin_reporter *reporter)
{
	this->tintin = reporter;
}

void		Server::checkClientLogged(void)
{
	for (int i = 0; i < SERV_CLIENTS; i++) {
		if (this->client[i].fd > -1 && !this->client[i].logged) {
			time_t timer = time(NULL);
			if (timer - this->client[i].log_time > SERV_LOG_TIME) {
				write(this->client[i].fd, "Loggin' timeout.\n", 17);
				close(this->client[i].fd);
				mymemset(&this->client[i].fd, 0, sizeof(t_client));
				this->client[i].fd = -1;
			}
		}
	}
}

void		Server::loopServ(void)
{
	int		maxfd;
	int		ret;
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (this->loop)
	{
		if (this->protect)
			Server::checkClientLogged();
		maxfd = Server::setupSelect();
		ret = select(maxfd + 1, &this->fdr, NULL, NULL, &timeout);
		if (ret == -1)
			throw DAEMONException("select");
		else if (ret > 0)
		{
			if (FD_ISSET(this->servfd, &this->fdr))
				acceptConnections();
			for (int i = 0; i < SERV_CLIENTS; i++) {
				if (this->client[i].fd > -1 &&
					FD_ISSET(this->client[i].fd, &this->fdr))
					clientRead(this->client[i]);
			}
		}
	}
}

int			Server::setupSelect(void)
{
	int		i;
	int		max;

	FD_ZERO(&this->fdr);
	FD_SET(this->servfd, &this->fdr);
	max = this->servfd;
	i = 0;
	while (i < SERV_CLIENTS)
	{
		if (this->client[i].fd > max)
			max = this->client[i].fd;
		if (this->client[i].fd > -1)
			FD_SET(this->client[i].fd, &this->fdr);
		i++;
	}
	return max;
}

void		Server::acceptConnections(void)
{
	struct sockaddr	csin;
	struct sockaddr_in *cs	= (struct sockaddr_in *)&csin;
	socklen_t		len		= sizeof(csin);
	int				i		= 0;
	int				fd;

	fd = accept(this->servfd, &csin, &len);
	if (fd < 0)
		throw DAEMONException("accept");
	
	inet_ntop(AF_INET, &cs->sin_addr.s_addr, this->client[i].addr, 1024);
	getnameinfo(&csin, sizeof(csin), this->client[i].host, NI_MAXHOST, this->client[i].port, NI_MAXSERV, NI_NUMERICSERV);
	i = 0;
	while (i < SERV_CLIENTS && this->client[i].fd != -1)
		i++;
	if (i < SERV_CLIENTS) {
		this->tintin->log("INFO", "New connection from %S(%S):%S accepted.",
						  this->client[i].host,
						  this->client[i].addr, this->client[i].port);
		this->client[i].fd = fd;
		this->client[i].log_time = time(NULL);
		this->nb_clients++;
	}
	else {
		this->tintin->log("INFO", "New connection from %S(%S):%S rejected.",
						  this->client[i].host,
						  this->client[i].addr, this->client[i].port);
		write(fd, "Server full.\n", 13);
		close(fd);
	}
}

void		Server::clientRead(t_client & cl)
{
	static const char	*cmds[] = { SERV_CMDS, NULL };
	static void	(Server::*funcs[])(t_client &) = { SERV_FUNCS };
	int			ret;
	char		buff[SERV_BUFF];

	ret = recv(cl.fd, buff, SERV_BUFF - 1, 0);
	if (ret <= 0)
	{
		this->tintin->log("INFO", "%S(%S):%S has disconnected.",
							cl.host, cl.addr, cl.port);
		close(cl.fd);
		mymemset(&cl, 0, sizeof(t_client));
		cl.fd = -1;
		this->nb_clients--;
		return ;
	}
	buff[ret] = '\0';
	cl.cmd += buff;
	std::size_t found;
	while ((found = cl.cmd.find_first_of('\n')) != std::string::npos)
	{
		cl.cmd.at(found) = 0;
		if (this->protect && !cl.logged) {
			;
		} else {
			int j;
			for (j = 0; cmds[j]; j++) {
				if (cl.cmd.compare(cmds[j]) == 1) {
					this->tintin->log("INFO", "Request %S.", cmds[j]);
					(this->*funcs[j])(cl);
					break ;
				}
			}
			if (!cmds[j])
				this->tintin->log("LOG", "%S:%S : %s",
									cl.host, cl.port, cl.cmd);
		}
		cl.cmd = cl.cmd.substr(found + 1);
	}
}

void *		Server::mymemset(void *s, int c, size_t n) const
{
	char	*t = (char *)s;

	while (n--)
		*t++ = c;
	return s;
}

void		Server::sendLog(t_client &cl)
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

void		Server::sendInfo(t_client &cl)
{
	std::string		info;
	struct ifaddrs	*ifstruct	= NULL;
	struct ifaddrs	*ifs		= NULL;
	void			*addr		= NULL;
	const char		*cmds[]		= { SERV_CMDS, NULL };

	getifaddrs(&ifstruct);
	info = "Daemon written by GBOURGEO for 42.\n";
	info += "Daemon started on ";
	info += ctime(&this->start_time);
	info += "\nIp version\tService\tAddress\t\tPort\n";
	info += "---------------------------------------------";
	info += "---------------------------------------------\n";
	for (ifs = ifstruct; ifs != NULL; ifs = ifs->ifa_next) {
		if (!ifs->ifa_addr)
			continue ;
		if (ifs->ifa_addr->sa_family == AF_INET) {
			addr = &((struct sockaddr_in *)ifs->ifa_addr)->sin_addr;
			char	buf[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, addr, buf, INET_ADDRSTRLEN);
			info += "v4\t";
			info += ifs->ifa_name;
			info += '\t';
			info += buf;
			info += (strlen(buf) > 11) ? "\t" : "\t\t";
			info += SERV_PORT;
			info += '\n';
		}
		else if (ifs->ifa_addr->sa_family == AF_INET) {
			addr = &((struct sockaddr_in6 *)ifs->ifa_addr)->sin6_addr;
			char	buf[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, addr, buf, INET6_ADDRSTRLEN);
			info += "v6\t";
			info += ifs->ifa_name;
			info += '\t';
			info += buf;
			info += (strlen(buf) > 11) ? "\t" : "\t\t";
			info += SERV_PORT;
			info += '\n';
		}
	}
	if (ifstruct)
		freeifaddrs(ifstruct);
	info += "\nDaemon max. clients:  " + std::to_string(SERV_CLIENTS) + "\n";
	info += "Daemon curr. clients:  " + std::to_string(this->nb_clients) + "\n";
	info += "Daemon encrypted version : ";
	info += (SERV_ENCRYPT) ? "Yes" : "No";
	info += '\n';
	info += "Daemon passwd protected : ";
	info += (SERV_PROTECT) ? "Yes" : "No";
	info += '\n';
	info += "Daemon commands avail. :  ";
	for (int i = 0; cmds[i]; i++) {
		info += "\"";
		info += cmds[i];
		info += '"';
		info += (cmds[i + 1]) ? ", " : ".";
	}
	info += '\n';
	write(cl.fd, &info[0], info.size());
}

void		Server::quit(t_client &cl)
{
	(void)cl;
	for (int i = 0; i < SERV_CLIENTS; i++)
		write(this->client[i].fd, "Request quit received.\n", 23);
	this->loop = false;
}
