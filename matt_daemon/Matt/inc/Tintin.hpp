// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:47:05 by root              #+#    #+#             //
//   Updated: 2017/11/21 23:47:16 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TINTIN_HPP
# define TINTIN_HPP

# define LOG_DIR	"/var/log/matt_daemon/"
# define LOG_FILE	"/var/log/matt_daemon/matt_daemon.log"

# include <iostream>
# include <fstream>
# include <cstdarg>

class			Tintin_reporter
{

public:
	Tintin_reporter();
	Tintin_reporter(const Tintin_reporter & rhs);
	~Tintin_reporter();
	Tintin_reporter & operator=(Tintin_reporter const & rhs);
	
	void	log(const std::string & title, const std::string & info, va_list ap);
	void	clearLogs( void );

private:
	std::ofstream	_logfd;
	std::string		_buff;

};

#endif
