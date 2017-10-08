// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/10/02 22:58:19 by root             ###   ########.fr       //
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
# define SERV_ENCRYPT	false
# define SERV_PROTECT	false
# define SERV_LOG_TIME	2

# define SERV_CMDS		"log", "info", "quit"
# define SERV_FUNCS		&Server::sendLog, &Server::sendInfo, &Server::quit
# define SERV_BUFF		256

typedef struct		s_client
{
	int				fd;
	char			addr[1024];
	char			host[NI_MAXHOST];
	char			port[NI_MAXSERV];
	time_t			log_time;
	bool			logged;
	std::string		cmd;
}					t_client;

class		Server
{
	
public:
	Server(void);
	Server(Server const & src);
	~Server(void);

	Server & operator=(Server const & rhs);

	void		loopServ(void);
	void		setReporter(Tintin_reporter *reporter);
	
private:
	int			findSocket(struct addrinfo *p);
	void		setupSignals(void);
	void		sigHandler(int sig);
	int			setupSelect(void);
	void		checkClientLogged(void);
	void		acceptConnections(void);
	void		clientRead(t_client & clt);
	void		*mymemset(void *s, int c, size_t n) const;
	void		sendLog(t_client & cl);
	void		sendInfo(t_client & cl);
	void		quit(t_client & cl);

	Tintin_reporter *tintin;
	int			servfd;
	fd_set		fdr;
	t_client	client[SERV_CLIENTS];
	bool		loop;
	time_t		start_time;
	size_t		nb_clients;
	bool		encrypt;
	bool		protect;
};

#endif
