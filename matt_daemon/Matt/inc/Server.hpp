// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/09/29 04:36:10 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"
# include <sys/select.h>
# include <netdb.h>

# define SERV_ADDR		"localhost"
# define SERV_PORT		"4242"
# define SERV_CLIENTS	3

typedef struct		s_client
{
	int				fd;
	char			addr[1024];
	char			host[NI_MAXHOST];
	char			port[NI_MAXSERV];
}					t_client;

class		Server
{
	
public:
	Server(void);
	Server(Server const & src);
	~Server(void);

	Server & operator=(Server const & rhs);

	void		loopServ(Tintin_reporter *tintin);

private:
	int			findSocket(struct addrinfo *p);
	void		setupSignals(void);
	void		sigHandler(int sig);
	int			setupSelect(void);
	void		acceptConnections(Tintin_reporter *tintin);
	void		clientRead(Tintin_reporter *tintin);
	void *		mymemset(void *s, int c, size_t n);

	int			servfd;
	fd_set		fdr;
	t_client	client[SERV_CLIENTS];
	bool		loop;

};

#endif
