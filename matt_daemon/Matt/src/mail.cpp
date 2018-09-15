// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mail.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:42:22 by root              #+#    #+#             //
//   Updated: 2018/09/15 18:30:04 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "mail.hpp"
#include "stdlib_func.hpp"
#include "getSocket.hpp"
#include <unistd.h>

static const std::string ssh_err[] = { "The TLS/SSL I/O operation completed.",
										"The TLS/SSL connection has been closed.",
										"The SSL_ERROR_WANT_READ operation did not complete.",
										"The SLL_ERROR_WANT_WRITE operation did not complete.",
										"The SSL_ERROR_WANT_CONNECT operation did not complete.",
										"The SSL_ERROR_WANT_ACCEPT operation did not complete.",
										"The SSL_ERROR_WANT_X509_LOOKUP operation did not complete.",
										"Some I/O error occurred.",
										"A failure in the SSL library occurred." };

static int		getWhatToSend(t_client & cl)
{
	int			tosend = 0;

	for (const char *ptr = mystrchr(&cl.rd[0], ' '); ptr != NULL; ptr = mystrchr(ptr, ' ')) {
		ptr++;
		int ret;
		if ((ret = mystrcmp(ptr, "daemoninfo")) == 0 || ret == ' ')
			tosend |= SEND_DAEMONINFO;
		else if ((ret = mystrcmp(ptr, "machinfo")) == 0 || ret == ' ')
			tosend |= SEND_MACHINFO;
		else if ((ret = mystrcmp(ptr, "servinfo")) == 0 || ret == ' ')
			tosend |= SEND_SERVICEINFO;
		else if ((ret = mystrcmp(ptr, "daemonlogs")) == 0 || ret == ' ')
			tosend |= SEND_DAEMONLOGS;
		else if ((ret = mystrcmp(ptr, "all")) == 0 || ret == ' ')
			tosend |= SEND_ALL;
	}
	return tosend;
}

bool				Server::sendMailCorpse( std::string plaintext, t_client & cl )
{
	int					tosend = getWhatToSend(cl);
//	std::string			plaintext = "";
	const std::string	nl = "\r\n";

	plaintext += std::string("From: ") + std::string(MAIL_HEADER_FROM) + nl;
	plaintext += std::string("To: ") + std::string(MAIL_HEADER_TO) + nl;
	plaintext += std::string("Subject: ") + std::string(MAIL_HEADER) + nl;
	plaintext += std::string("MIME-Version: 1.0") + nl;
	if (tosend & SEND_DAEMONLOGS) {
		plaintext += std::string("Content-type: multipart/mixed; boundary=KJhfBYTXFNDVC98udV8S5") + nl + nl;
		plaintext += std::string("--KJhfBYTXFNDVC98udV8S5") + nl;
	}
	plaintext += std::string("Content-type: text/plain; charset=US-ASCII") + nl + nl;
	if (tosend & SEND_DAEMONINFO)
		plaintext += getDaemonInfo() + nl;
	if (tosend & SEND_MACHINFO)
		plaintext += getMachineInfo() + nl;
	if (tosend & SEND_SERVICEINFO)
		plaintext += getServiceInfo() + nl;
	if (tosend & SEND_DAEMONLOGS) {
		plaintext += std::string("--KJhfBYTXFNDVC98udV8S5") + nl;
		plaintext += std::string("Content-type: text/plain") + nl;
		plaintext += std::string("Content-Transfer-Encoding: base64") + nl;
		plaintext += std::string("Content-Disposition: attachment; filename=Daemon_Logs.txt") + nl + nl;
		std::string logs = getDaemonLogs();
		plaintext += logs + nl + nl;
		plaintext += std::string("--KJhfBYTXFNDVC98udV8S5") + nl;
	}		
	plaintext += std::string("\r\n.\r\n");
	writeMail(plaintext, cl);
	return true;
}

void			Server::sendMail(t_client &cl)
{
	int			tosend = getWhatToSend(cl);

	if (tosend == 0) {
		cl.wr += "Nothing to send.\r\n";
		cl.wr += "Usage: mail [[daemoninfo], [machinfo], [servinfo], [daemonlogs], [all]].\r\n";
		return ;
	}
	if (SSHConnection(cl) == false)
		return ;
	t_mail		msg[] = { { "220", std::string("EHLO ") + std::string(MAIL_DOMAIN), &Server::writeMail},
						  { "250", std::string("AUTH LOGIN"), &Server::writeMail },
						  { "334", std::string(AUTH_UID), &Server::writeMail },
						  { "334", std::string(AUTH_PWD), &Server::writeMail },
						  { "235", std::string("MAIL FROM: ") + std::string(MAIL_FROM), &Server::writeMail },
						  { "250", std::string("RCPT TO: ") + std::string(MAIL_TO), &Server::writeMail },
						  { "250", std::string("DATA"), &Server::writeMail },
						  { "354", std::string(""), &Server::sendMailCorpse },
						  { "250", std::string(), NULL } };
	bool		ret = true;

	for (size_t i = 0; i < sizeof(msg) / sizeof(*msg); i++) {
		if (!(ret = readMail(msg[i].nb, cl)))
			return ;
		if (msg[i].func && !(ret = CALL_MEMBER_FN(*this, msg[i].func)(msg[i].msg, cl)))
			return ;
	}
	if (this->ssl) {
		while (!SSL_shutdown(this->ssl)) ;
		SSL_clear(this->ssl);
		SSL_free(this->ssl);
		this->ssl = NULL;
	}
	if (this->mailfd != -1) {
		close(this->mailfd);
		this->mailfd = -1;
	}
	cl.wr += "Mail sent.\r\n";
}

bool			Server::SSHConnection( t_client & cl )
{
	int					ret;

	if ((this->mailfd = getSocket(SMTP_SERVER_URL, SMTP_SERVER_PORT, &mailSocket)) == -1)
		return mailError("Can't open mail socket", cl);
	if ((this->ssl = SSL_new(this->ctx)) == NULL) {
		std::string err = std::string("SLL session not created: ");
		err += std::string(ERR_error_string(ERR_get_error(), NULL));
		return mailError(&err[0], cl);
	}
	SSL_set_fd(this->ssl, this->mailfd);
	if ((ret = SSL_connect(this->ssl)) != 1) {
		std::string err = std::string("SLL session not connected: ");
		int val = SSL_get_error(this->ssl, ret);
		err += ssh_err[val];
		return mailError(&err[0], cl);
	}
	return true;
}

bool			Server::writeMail( std::string msg, t_client & cl )
{
	size_t		len;
	int			ret;

	msg += "\r\n";
	len = msg.size();
	ret = 0;
	while (this->ssl && len)
	{
		ret += SSL_write(this->ssl, &msg[ret], len);
		if (ret == 0)
			return mailError("Connection lost while write.", cl);
		if (ret < 0) {
			int val = SSL_get_error(this->ssl, ret);
			if (SSL_ERROR_WANT_WRITE == val)
				continue ;
			std::string err = std::string("SSL_WRITE: ");
			err += ssh_err[val];
			return mailError(&err[0], cl);
		}
		else
			len -= ret;
	}
	return true;
}

bool			Server::readMail( const char *code, t_client & cl )
{
	char		rcv[128] = {0};
	int			ret = 0;
	std::string	rd;

	while (this->ssl)
	{
		ret = SSL_read(this->ssl, rcv, sizeof(rcv) - 1);
		if (ret == 0)
			return mailError("Connection lost while read.", cl);
		if (ret < 0) {
			int val = SSL_get_error(this->ssl, ret);
			if (SSL_ERROR_WANT_READ != val)
				continue ;
			std::string err = std::string("SSL_READ: ");
			err += ssh_err[val];
			return mailError(&err[0], cl);
		}
		rcv[ret] = 0;
		rd += std::string(rcv);
		for (const char *str = rd.c_str(), *ptr = mystrchr(str, '\n');
			 ptr;
			 str = ptr + 1, ptr = mystrchr(str, '\n'))
		{
			if (mystrcmp(str, code) == ' ')
				return true;
			if (mystrcmp(str, code) == '-')
				continue ;
			return mailError(rd.c_str(), cl);
		}

	}
	return mailError(rd.c_str(), cl);
}

bool		Server::mailError(const char *err, t_client & cl)
{
	Server::log("ERROR", err);
	cl.wr += "Mail not sent:\n";
	cl.wr += err;
	cl.wr += "\n";
	if (this->ssl) {
		while (!SSL_shutdown(this->ssl)) ;
		SSL_clear(this->ssl);
		SSL_free(this->ssl);
		this->ssl = NULL;
	}
	if (this->mailfd != -1) {
		close(this->mailfd);
		this->mailfd = -1;
	}
	ERR_free_strings();
	return false;
}
