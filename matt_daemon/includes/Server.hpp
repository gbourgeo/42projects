// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/14 23:45:23 by gbourgeo          #+#    #+#             //
//   Updated: 2017/09/08 03:00:39 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

class Server
{

public:
	Server();
	Server(const Server&);
	~Server();
	Server & operator=(Server const & rhs);

private:
	sigset_t	oldmask;
	int			logfd;
};
