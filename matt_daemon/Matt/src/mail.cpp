// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mail.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:42:22 by root              #+#    #+#             //
//   Updated: 2017/10/22 14:59:14 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "mail.hpp"
#include "stdlib_func.hpp"
#include "getSocket.hpp"
#include "base64.hpp"
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

	for (const char *ptr = mystrchr(&cl.cmd[0], ' '); ptr != NULL; ptr = mystrchr(ptr, ' ')) {
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

void				Server::sendMailCorpse( t_client & cl )
{
	int					tosend = getWhatToSend(cl);
	std::string			plaintext = "";
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
}

void			Server::sendMail(t_client &cl)
{
	int			tosend = getWhatToSend(cl);

	if (tosend == 0) {
		write(cl.fd, "Nothing to send.\r\n", 18);
		return ;
	}
	if (SSHConnection(cl) == false)
		return ;
	readMail("220", cl);
	writeMail(std::string("EHLO ") + std::string(MAIL_DOMAIN), cl);
	readMail("250", cl);
	writeMail(std::string("AUTH LOGIN"), cl);
	readMail("334", cl);
	writeMail(std::string(AUTH_UID), cl);
	readMail("334", cl);
	writeMail(std::string(AUTH_PWD), cl);
	readMail("235", cl);
	writeMail(std::string("MAIL FROM: ") + std::string(MAIL_FROM), cl);
	readMail("250", cl);
	writeMail(std::string("RCPT TO: ") + std::string(MAIL_TO), cl);
	readMail("250", cl);
	writeMail(std::string("DATA"), cl);
	readMail("354", cl);
	sendMailCorpse(cl);
	readMail("250", cl);
	if (this->ssl) {
		while (!SSL_shutdown(this->ssl))
			;
		SSL_clear(this->ssl);
		SSL_free(this->ssl);
		this->ssl = NULL;
	}
	if (this->mailfd != -1) {
		close(this->mailfd);
		this->mailfd = -1;
	}
	write(cl.fd, "Mail sent.\r\n", 12);
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
	while (len)
	{
		ret += SSL_write(ssl, &msg[ret], len);
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

	while (true)
	{
		ret = SSL_read(this->ssl, rcv, sizeof(rcv) - 1);
		if (ret == 0)
			return mailError("Connection lost while read.", cl);
		if (ret < 0) {
			int val = SSL_get_error(this->ssl, ret);
			if (SSL_ERROR_WANT_READ != val)
				continue ;
			std::string err = std::string("SSL_WRITE: ");
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
	this->tintin->log("ERROR", err);
	write(cl.fd, err, mystrlen(err));
	write(cl.fd, "\n", 1);
	if (this->ssl) {
		while (!SSL_shutdown(this->ssl))
			;
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
