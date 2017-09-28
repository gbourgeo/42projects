// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Exceptions.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/13 18:58:54 by root              #+#    #+#             //
//   Updated: 2017/09/24 08:53:56 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Exceptions.hpp"

DAEMONException::DAEMONException( void ) throw() : str(NULL)
{
}

DAEMONException::DAEMONException( const char *str ) throw() : str(str)
{
}

const char* DAEMONException::what() const throw()
{
	if (errno)
		return strerror(errno);
	return this->str;
}

std::string DAEMONException::explain() const throw()
{
	std::string str;

	str = this->str;
	if (errno)
		str += ": " + (std::string)strerror(errno);
	return str;
}
