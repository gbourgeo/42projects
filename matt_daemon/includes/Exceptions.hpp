// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Exceptions.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/13 02:34:47 by root              #+#    #+#             //
//   Updated: 2017/09/13 22:28:53 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

# include <stdexcept>
# include <string.h>
# include <errno.h>

class			DAEMONException : public std::exception
{

public:
	DAEMONException( void ) throw();
	DAEMONException( const char * str ) throw();
	virtual char const* what() const throw();

	char const*		str;

};

#endif
