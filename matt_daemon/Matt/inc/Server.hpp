// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/11/05 23:45:18 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"
# include "mail.hpp"
# include "common.hpp"
# include <sys/select.h>
# include <netdb.h>

# define SERV_ADDR			"localhost"
# define SERV_PORT			"4242"
# define SERV_MSG_ENCRYPTED	true
# define SERV_PWD_PROTECTED	false
# define SERV_PWD			""
# define SERV_MAX_CLIENTS	3
# define SERV_LOGGIN_TIME	2

# define SERV_CMDS			{ { "daemonlogs", "Prints the Daemon log file." }, \
							  { "daemoninfo", "Shows informations about the Daemon itself." }, \
							  { "daemonpwd", "Changes the Daemon protection. TRUE with an argument (will be the new password) or FALSE with no argument." }, \
							  { "machinfo", "Gives informations about the machine the Daemon is running on." }, \
							  { "servinfo", "Gives informations about the services of the machine the Daemon is runing on." }, \
							  { "clearlogs", "Clears the Daemon log file." }, \
							  { "mail", "Sends an email with informations related to the parameters given (daemonlogs, machinfo, etc...)."}, \
							  { "quit", "Shutdown the Daemon." },		\
							  { NULL, NULL }, }

# define SERV_FUNCS			{ &Server::sendDaemonLogs,		\
							  &Server::sendDaemonInfo,		\
							  &Server::setDaemonPwd,		\
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
	std::string	rd;
	std::string	wr;
	std::string	wr_encoded;
}				t_client;

class			Server
{
	
public:
	Server(void);
	Server(Server const & src);
	~Server(void);

	Server & operator=(Server const & rhs);

	void		mailMeDaemonInfo( void );
	void		launchServer( void );
	void		setReporter( Tintin_reporter *reporter );

	std::string		quitReason;
	
private:
	void		setupSignals( void );
	void		sigHandler( int sig );
	int			setupSelect( void );
	void		acceptConnections( void );
	void		clientRead( t_client & cl );
	void		clientWrite(t_client & cl);
	void		clientQuit(const char * reason, t_client & cl);
	void		clientCommands( t_client & cl );
	void		sendDaemonLogs( t_client & cl );
	void		sendDaemonInfo( t_client & cl );
	void		setDaemonPwd( t_client & cl );
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
	fd_set			fdw;
	bool			loop;
	time_t			start_time;
	size_t			nb_clients;
	t_client		client[SERV_MAX_CLIENTS];
	SSL_CTX *		ctx;
	SSL *			ssl;
	bool			protect;
	std::string		passwd;
	bool			encrypt;
};

#endif
