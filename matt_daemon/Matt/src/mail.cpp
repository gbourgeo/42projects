// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mail.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:42:22 by root              #+#    #+#             //
//   Updated: 2017/10/16 00:07:08 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "mail.hpp"
#include "stdlib_func.hpp"
#include <string.h>
#include <openssl/bio.h>
#include <openssl/err.h>

void		Server::sendMail(t_client &cl)
{
	const SSL_METHOD *	method;
	SSL_CTX *			ctx;
	SSL *				ssl;
	static const std::string nl = "\r\n";

	SSL_library_init();
	OpenSSL_add_ssl_algorithms();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	if (SSL_library_init() < 0)
		return mailError("OpenSSL not initialized");
	method = SSLv23_client_method();
	if ((ctx = SSL_CTX_new(method)) == NULL)
		return mailError("OpenSSL context not initialized");
	SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2);
	ssl = SSL_new(ctx);
	/* We normally have our mailFD here...*/
	SSL_set_fd(ssl, this->mailfd);
	if (SSL_connect(ssl) != 1)
		return mailError("SLL session not created");

	readMail(ssl, "220");
	writeMail(ssl, std::string("EHLO ") + std::string(MAIL_DOMAIN) + nl);
	readMail(ssl, "250");
	writeMail(ssl, std::string("AUTH LOGIN") + nl);
	readMail(ssl, "334");
	writeMail(ssl, std::string(AUTH_UID) + nl);
	readMail(ssl, "334");
	writeMail(ssl, std::string(AUTH_PWD) + nl);
	readMail(ssl, "235");
	writeMail(ssl, std::string("MAIL FROM: ") + std::string(MAIL_FROM) + nl);
	readMail(ssl, "250");
	writeMail(ssl, std::string("RCPT TO: ") + std::string(MAIL_TO) + nl);
	readMail(ssl, "250");
	writeMail(ssl, std::string("DATA") + nl);
	readMail(ssl, "354");
	writeMail(ssl, std::string("From: ") + std::string(MAIL_HEADER_FROM) + nl);
	writeMail(ssl, std::string("To: ") + std::string(MAIL_HEADER_TO) + nl);
	writeMail(ssl, std::string("Subject: ") + std::string(MAIL_HEADER) + nl);
	writeMail(ssl, std::string("MIME-Version: 1.0") + nl);
	writeMail(ssl, std::string("Content-type: text/plain; charset=US-ASCII" + nl + nl));
	writeMail(ssl, std::string("coucou") + nl);
	writeMail(ssl, nl + std::string(".") + nl);
	readMail(ssl, "250");
	
	ERR_free_strings();
	(void)cl;
}

bool			Server::writeMail( SSL *ssl, std::string msg )
{
	const char	*str = msg.c_str();
	int ret = 0;

	ret = SSL_write(ssl, str, mystrlen(str));
	if (ret == 0) {
		mailError("Connection lost while write.");
		return false;
	}
	if (ret < 0) {
		mailError("Socket write failed.");
		return false;
	}
	return true;
}

bool			Server::readMail( SSL *ssl, const char *code )
{
	char		rcv[128] = {0};
	int			ret = 0;
	std::string	rd;

	while (true)
	{
		ret = SSL_read(ssl, rcv, sizeof(rcv) - 1);
		if (ret == 0) {
			mailError("Connection lost while read.");
			return false;
		}
		if (ret < 0 && SSL_ERROR_WANT_READ == SSL_get_error(ssl, ret))
			continue ;
		rcv[ret] = 0;
		rd += std::string(rcv);
		for (const char *str = rd.c_str(), *ptr = mystrchr(str, '\n');
			 ptr;
			 str = ptr + 1, ptr = mystrchr(str, '\n'))
		{
			if (mystrcmp(str, code) == '-')
				continue ;
			else if (mystrcmp(str, code) == ' ')
				return true;
			else if (ptr - str >= 3 && *(str + 3) == ' ') {
				mailError(rd.c_str());
				return false;
			}
		}
	}
	mailError(rd.c_str());
	return false;
}

void		Server::mailError(const char *err)
{
	this->tintin->log("ERROR", err);
	ERR_free_strings();
}
