// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Logger.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 19:52:06 by root              #+#    #+#             //
//   Updated: 2018/06/29 21:22:16 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <ctime>
#include "Logger.hpp"

Logger::Logger(std::string const & filename): _filename(filename)
{
	_file.open(_filename.c_str(), std::ios::app);
}

Logger::~Logger()
{
	if (_file.is_open())
		_file.close();
}

void Logger::log(std::string const & dest, std::string const & message)
{
	static std::string		output[] = { "console", "file" };
	static LoggerType		logs[] = { &Logger::_logToConsole, &Logger::_logToFile };
	std::size_t				i = 0;

	while (i < sizeof(output) / sizeof(*output))
	{
		if (dest == output[i]) {
			(this->*logs[i])(message);
			break ;
		}
		i++;
	}
}

void Logger::_logToConsole(std::string const & str)
{
	char			date[100];
	std::time_t		t = std::time(NULL);
	std::string		logged;

	if (std::strftime(date, sizeof(date), "[%Y%m%d_%H%M%S] ", std::localtime(&t)))
		std::cout << date;
	std::cout << str << std::endl;
}

void Logger::_logToFile(std::string const & str)
{
	char			date[100];
	std::time_t		t = std::time(NULL);
	std::string		logged;

	if (std::strftime(date, sizeof(date), "[%Y%m%d_%H%M%S] ", std::localtime(&t)))
		_file << date;
	_file << str << std::endl;
}

std::string Logger::_makeLogEntry(std::string str)
{
	char			date[100];
	std::time_t		t = std::time(NULL);
	std::string		logged;

	if (std::strftime(date, sizeof(date), "[%Y%m%d_%H%M%S] ", std::localtime(&t)))
		logged = date;
	logged += str;
	return logged;
}
