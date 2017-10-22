// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/10/22 14:58:55 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"
# include "mail.hpp"
# include <sys/select.h>
# include <netdb.h>

# define SERV_ADDR			"localhost"
# define SERV_PORT			"4242"
# define SERV_ENCRYPT		false
# define SERV_PROTECT		false
# define SERV_CLIENTS		3
# define SERV_LOGGIN_TIME	2
# define SERV_BUFF			256
# define SERV_CMDS			{ "daemonlogs",			\
							  "daemoninfo",			\
							  "machinfo",			\
							  "servinfo",			\
							  "clearlogs",			\
							  "mail",				\
							  "quit", NULL }
# define SERV_FUNCS			{ &Server::sendDaemonLogs,		\
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
	void		setupSignals( void );
	void		sigHandler( int sig );
	int			setupSelect( void );
	void		checkClientLogged( void );
	void		acceptConnections( void );
	void		clientRead( t_client & cl );
	void		clientCommands( t_client & cl );
	void		sendDaemonLogs( t_client & cl );
	void		sendDaemonInfo( t_client & cl );
	void		sendMachineInfo( t_client & cl );
	void		sendServiceInfo( t_client & cl );
	void		clearDaemonLogs( t_client & cl );
	void		sendMail( t_client & cl );
	void		sendMailCorpse( t_client & cl );
	bool		SSHConnection( t_client & cl );
	bool		readMail( const char *code, t_client & cl );
	bool		writeMail( std::string msg, t_client & cl );
	bool		mailError(const char *err, t_client & cl );
	void		quit(t_client & cl);

	std::string		getDaemonLogs( void );
	std::string		getDaemonInfo( void );
	std::string		getMachineInfo( void );
	std::string		getServiceInfo( void );

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
	SSL_CTX *		ctx;
	SSL *			ssl;
};

#endif
