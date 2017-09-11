// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:09 by root              #+#    #+#             //
//   Updated: 2017/09/11 06:17:19 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SERVER_HPP
# define SERVER_HPP

# define SERV_ADDR "localhost"
# define SERV_PORT "4242"
# define SERV_CLIENTS 3

class		Server
{
	
public:
	Server(void);
	Server( Server const & src);
	~Server( void);

	Server & operator=(Server const & rhs);

	int			getServfd(void) const;
	const char	*getError(void) const;
	
	int			servfd;
	const char	*err;

private:
	int findSocket(struct addrinfo *p);

};

#endif
