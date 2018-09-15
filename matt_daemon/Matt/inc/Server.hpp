// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2018/09/15 18:29:31 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Tintin.hpp"
# include "mail.hpp"
# include "common.hpp"
# include <sys/select.h>
# include <netdb.h>
# include <vector>

# define SERV_ADDR			"localhost"
# define SERV_PORT			"4242"
# define SERV_MSG_ENCRYPTED	false
# define SERV_PASS_PROTECTD	false
# define SERV_PASSWD		""
# define SERV_MAX_CLIENTS	3
# define SERV_LOGGIN_TIME	2

# define SERV_CMDS			{ { "daemonlogs", "Prints the Daemon log file." }, \
							  { "daemoninfo", "Shows informations about the Daemon itself." }, \
							  { "daemonpass", "Changes the Daemon protection status.\n\t\t"	\
								"TRUE with an argument (will be the new password).\n\t\t" \
								"FALSE with no argument." },			\
							  { "daemoncrypt", "Changes the Daemon messages status." }, \
							  { "machinfo", "Gives informations about the machine the Daemon\n\t\t"	\
								"is running on." },						\
							  { "servinfo", "Gives informations about the services of the\n\t\t" \
								"machine the Daemon is runing on." },	\
							  { "clearlogs", "Clears the Daemon log file." }, \
							  { "mail", "Sends an email with informations related to the\n\t\t"	\
								"parameters given (daemonlogs, machinfo, ..., all)."}, \
							  { "quit", "Shutdown the Daemon." },		\
							  { NULL, NULL }, }

# define SERV_FUNCS			{ &Server::sendDaemonLogs,		\
							  &Server::sendDaemonInfo,		\
							  &Server::setDaemonPasswd,		\
							  &Server::setDaemonCrypted,	\
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

	typedef struct	s_mail
	{
		const char	*nb;
		std::string	msg;
		bool		(Server::*func)(std::string, t_client &);
	}				t_mail;

	Server(void);
	Server(Server const & src);
	~Server(void);

	Server & operator=(Server const & rhs);

	void		mailMeDaemonInfo( void );
	void		launchServer( void );
	void		setReporter( Tintin_reporter *reporter );

	std::string		quitReason;
	
private:
	void		log(const std::string & title, const std::string & info, ...);
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
	void		setDaemonPasswd( t_client & cl );
	void		setDaemonCrypted( t_client & cl);
	void		sendMachineInfo( t_client & cl );
	void		sendServiceInfo( t_client & cl );
	void		clearDaemonLogs( t_client & cl );
	void		clearClient( t_client & cl);
	void		sendMail( t_client & cl );
	bool		sendMailCorpse( std::string plaintext, t_client & cl );
	bool		SSHConnection( t_client & cl );
	bool		readMail( const char *code, t_client & cl );
	bool		writeMail( std::string msg, t_client & cl );
	bool		mailError(const char *err, t_client & cl );
	void		quit(t_client & cl);

	std::string		getDaemonLogs( void );
	std::string		getDaemonInfo( void );
	std::string		getMachineInfo( void );
	std::string		getServiceInfo( void );
	void			sendAllClients(std::string & msg);

	const std::vector<std::string> split(const std::string &str, const char &c);
	
	Tintin_reporter *tintin;
	int				servfd;
	int				mailfd;
	fd_set			fdr;
	fd_set			fdw;
	bool			loop;
	time_t			start_time;
	size_t			nb_clients;
	t_client		client[SERV_MAX_CLIENTS + 1];
	SSL_CTX *		ctx;
	SSL *			ssl;
	bool			protect;
	std::string		passwd;
	bool			encrypt;
};

typedef bool (Server::*func)(std::string, t_client &);
# define CALL_MEMBER_FN(object,funcPtr)		((object).*(funcPtr))

#endif
