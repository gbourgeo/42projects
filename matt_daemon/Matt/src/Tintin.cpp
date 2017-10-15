// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:46:49 by root              #+#    #+#             //
//   Updated: 2017/10/11 20:55:11 by root             ###   ########.fr       //
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

void Tintin_reporter::log(const std::string & title, const std::string & info, ...)
{
	struct tm	*tm;
	time_t		t;

	if (!this->_logfd.is_open())
		return ;
	t = time(NULL);
	tm = localtime(&t);
	this->_logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	this->_logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	this->_logfd << "] [ " << title << " ] - Matt_daemon: ";

	size_t		i = 0, j = 0;
	va_list		ap;

	va_start(ap, info);
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
				std::string *ret = va_arg(ap, std::string *);
				if (ret)
					this->_buff.append(*ret);
			}
			else if (info[i] == 'S') {
				char *ret = va_arg(ap, char *);
				if (ret)
					this->_buff.append(ret);
			}
			j = i + 1;
		}
		i++;
	}
	va_end(ap);
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
