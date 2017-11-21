// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:46:49 by root              #+#    #+#             //
//   Updated: 2017/11/21 23:47:23 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Tintin.hpp"
#include "Exceptions.hpp"
#include <string>
#include <sys/types.h> //mkdir
#include <sys/stat.h>  //mkdir

Tintin_reporter::Tintin_reporter()
{
	mkdir(LOG_DIR, 0600);
	this->_logfd.exceptions( std::ofstream::failbit | std::ofstream::badbit);
	this->_logfd.open(LOG_FILE, std::ofstream::out | std::ofstream::app);
	if (!this->_logfd.is_open())
		throw DAEMONException("logfile");
}

Tintin_reporter::Tintin_reporter(const Tintin_reporter & rhs)
{
	*this = rhs;
}

Tintin_reporter::~Tintin_reporter()
{
	if (this->_logfd.is_open())
		this->_logfd.close();
}

Tintin_reporter & Tintin_reporter::operator=(Tintin_reporter const & rhs)
{
	(void)rhs;
	return *this;
}

/*
** Conversion supported:
**		%d: int
**		%s: char *
**		%S: std::string * (use with caution, it can lead to random bugs)
*/

void Tintin_reporter::log(const std::string & title, const std::string & info, va_list ap)
{
	size_t		i = 0, j = 0;
	struct tm	*tm;
	time_t		t;

	if (!this->_logfd.is_open())
		return ;
	t = time(NULL);
	tm = localtime(&t);
	this->_logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	this->_logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	this->_logfd << "] [ " << title << " ] - Matt_daemon: ";

	this->_buff.clear();
	while (info[i])
	{
		if (info[i] == '%')
		{
			this->_buff.append(&info[j], i - j);
			i++;
			if (info[i] == 'd') {
				int		ret = va_arg(ap, int);
				this->_buff += std::to_string(ret);
			}
			else if (info[i] == 's') {
				char *ret = va_arg(ap, char *);
				if (ret)
					this->_buff.append(ret);
			}
			// else if (info[i] == 'S') {
			// 	std::string *ret = va_arg(ap, std::string *);
			// 	if (ret)
			// 		this->_buff.append(*ret);
			// }
			else
				this->_buff.append("%");
			j = i + 1;
		}
		i++;
	}
	this->_buff.append(&info[j], i - j);
	this->_logfd << this->_buff << std::endl;
}

void		Tintin_reporter::clearLogs( void )
{
	if (!this->_logfd.is_open())
		return ;
	this->_logfd.close();
	this->_logfd.open(LOG_FILE, std::ofstream::out | std::ofstream::trunc);
	if (!this->_logfd.is_open())
		throw DAEMONException("logfile");
}
