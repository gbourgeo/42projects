// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/09/13 22:47:03 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"

# define SERV_ADDR "localhost"
# define SERV_PORT "4242"
# define SERV_CLIENTS 1
# define WORKING_DIR "/"
# include <sys/select.h>

int	mystrcmp(const char *s1, const char *s2);

class		Server
{
	
public:
	Server(void);
	Server( Server const & src);
	~Server( void);

	Server & operator=(Server const & rhs);

	void		loopServ(Tintin_reporter *tintin);

private:
	int			setupSelect(void);
	int			findSocket(struct addrinfo *p);
	void		acceptConnections(void);
	void		clientRead(Tintin_reporter *tintin);
	int			servfd;
	fd_set		fdr;
	int			cl[SERV_CLIENTS];
	bool		loop;

};

#endif
