// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/08 00:38:29 by root              #+#    #+#             //
//   Updated: 2017/09/08 02:35:15 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

Server::Server()
{

}

Server::Server(const Server&)
{

}

Server::~Server()
{
}

Server & Server::operator=(Server const & rhs)
{
	this->oldmask = rhs.oldmask;
	return *this;
}
