// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Logger.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 19:51:44 by root              #+#    #+#             //
//   Updated: 2018/06/29 21:19:44 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LOGGER_HPP
# define LOGGER_HPP

#include <string>
#include <fstream>

class Logger
{

public:
	Logger(std::string const & filename);
	~Logger();

	void			log(std::string const & dest, std::string const & message);
	
private:
	void			_logToConsole(std::string const & str);
	void			_logToFile(std::string const & str);

	std::string const &	_filename;
	std::ofstream		_file;

	std::string		_makeLogEntry(std::string str);
};

typedef void (Logger::*LoggerType)(std::string const &);

#endif
