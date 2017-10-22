// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   mail.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 18:46:02 by root              #+#    #+#             //
//   Updated: 2017/10/22 15:02:42 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIL_HPP
# define MAIL_HPP

# include <openssl/ssl.h>
# include <openssl/err.h>

/*
** If you connect to gmail, UID and PWD must be base64 encoded.
*/

#define SMTP_SERVER_URL		"smtp.gmail.com"
#define SMTP_SERVER_PORT	"465"
#define MAIL_DOMAIN			"localhost"
#define AUTH_UID			"Z2lsbGVzYm91cmdlb2lAZ21haWwuY29t"
#define AUTH_PWD			"Z3JBZmZJdEkwMDc="
#define MAIL_FROM			"<gillesbourgeoi@gmail.com>"
#define MAIL_TO				"<gillesbourgeoi@gmail.com>"
#define MAIL_HEADER			"Matt_Daemon Mail delivery"
#define MAIL_HEADER_FROM	"Matt Daemon"
#define MAIL_HEADER_TO		"Moi_meme"

# define SEND_DAEMONINFO	0x0001
# define SEND_MACHINFO		0x0010
# define SEND_SERVICEINFO	0x0100
# define SEND_DAEMONLOGS	0x1000
# define SEND_ALL			0x1111

#endif
