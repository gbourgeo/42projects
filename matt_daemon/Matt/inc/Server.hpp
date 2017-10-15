// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/10/15 23:13:10 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"
# include <sys/select.h>
# include <netdb.h>
# include <openssl/ssl.h>

# define SERV_ADDR		"localhost"
# define SERV_PORT		"4242"
# define SERV_CLIENTS	3
# define SERV_ENCRYPT	false
# define SERV_PROTECT	false
# define SERV_LOGGIN_TIME	2
# define SERV_BUFF		256
# define SERV_CMDS		{ "daemonlogs",			\
						  "daemoninfo",			\
						  "machinfo",			\
						  "servinfo",			\
						  "clearlogs",			\
						  "mail",				\
						  "quit", NULL }
# define SERV_FUNCS		{ &Server::sendDaemonLogs,		\
						  &Server::sendDaemonInfo,		\
						  &Server::sendMachineInfo,		\
						  &Server::sendServiceInfo,		\
						  &Server::clearDaemonLogs,		\
						  &Server::sendMail,			\
						  &Server::quit }

typedef struct	s_client
{
	int			fd;
	char		addr[1024];
	char		host[NI_MAXHOST];
	char		port[NI_MAXSERV];
	time_t		log_time;
	bool		logged;
	std::string	cmd;
}				t_client;

class			Server
{
	
public:
	Server(void);
	Server(Server const & src);
	~Server(void);

	Server & operator=(Server const & rhs);

	void		loopServ(void);
	void		setReporter(Tintin_reporter *reporter);
	
private:
	void		setupSignals(void);
	void		sigHandler(int sig);
	int			setupSelect(void);
	void		checkClientLogged(void);
	void		acceptConnections(void);
	void		clientRead(t_client & clt);
	void		clientCommands(t_client & clt);
	void		sendDaemonLogs(t_client & cl);
	void		sendDaemonInfo(t_client & cl);
	void		sendMachineInfo(t_client & cl);
	void		sendServiceInfo(t_client & cl);
	void		clearDaemonLogs(t_client & cl);
	void		sendMail(t_client &cl);
	bool		readMail(SSL *ssl, const char *code);
	bool		writeMail(SSL *ssl, std::string msg);
	void		mailError(const char *err);
	void		quit(t_client & cl);

	Tintin_reporter *tintin;
	int				servfd;
	int				mailfd;
	fd_set			fdr;
	bool			loop;
	time_t			start_time;
	size_t			nb_clients;
	bool			encrypt;
	bool			protect;
	t_client		client[SERV_CLIENTS];
};

#endif
