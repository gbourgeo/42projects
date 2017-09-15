// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Exceptions.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/13 18:58:54 by root              #+#    #+#             //
//   Updated: 2017/09/13 22:32:51 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Exceptions.hpp"

DAEMONException::DAEMONException( void ) throw() : str(NULL)
{
}

DAEMONException::DAEMONException( const char * str ) throw() : str(str)
{
}

char const * DAEMONException::what() const throw()
{
	return strerror(errno);
}
