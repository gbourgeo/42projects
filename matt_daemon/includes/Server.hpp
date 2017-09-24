// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/09/24 10:09:12 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"
# include <sys/select.h>

# define SERV_ADDR "localhost"
# define SERV_PORT "4242"
# define SERV_CLIENTS 3

class		Server
{
	
public:
	Server(void);
	Server( Server const & src);
	~Server( void);

	Server & operator=(Server const & rhs);

	void		loopServ(Tintin_reporter *tintin);
	void		quit();

private:
	int			findSocket(struct addrinfo *p);
	void		setupSignals(void);
	void		sigHandler(int sig);
	int			setupSelect(void);
	void		acceptConnections(void);
	void		clientRead(Tintin_reporter *tintin);
	int			mystrcmp(const char *s1, const char *s2);

	int			servfd;
	fd_set		fdr;
	int			cl[SERV_CLIENTS];
	bool		loop;

};

#endif
