// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:46:49 by root              #+#    #+#             //
//   Updated: 2017/09/13 22:44:10 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Tintin.hpp"
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

Tintin_reporter::Tintin_reporter()
{
	mkdir(LOG_DIR, 0600);
	this->_logfd.exceptions( std::ofstream::failbit | std::ofstream::badbit);
	this->_logfd.open(LOG_FILE, std::ofstream::out | std::ofstream::app);
}

Tintin_reporter::Tintin_reporter(const Tintin_reporter & rhs)
{
	*this = rhs;
}

Tintin_reporter::~Tintin_reporter()
{
	Tintin_reporter::log("INFO", "Quitting.");
	if (this->_logfd.is_open())
		this->_logfd.close();
	if (this->lockfd.is_open())
		this->lockfd.close();
}

Tintin_reporter & Tintin_reporter::operator=(Tintin_reporter const & rhs)
{
	(void)rhs;
	return *this;
}

void Tintin_reporter::log(const char *title, const char *info)
{
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	if (!this->_logfd.is_open())
		return ;
	this->_logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	this->_logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	this->_logfd << "] [ " << title << " ] - Matt_daemon: " << info << std::endl;
}

void Tintin_reporter::log(const char *title, const char *info, pid_t pid)
{
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	if (!this->_logfd.is_open())
		return ;
	this->_logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	this->_logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	this->_logfd << "] [ " << title << " ] - Matt_daemon: " << info;
	this->_logfd << pid << std::endl;
}

void Tintin_reporter::log(const char *title, const char *info, const char *buff)
{
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	if (!this->_logfd.is_open())
		return ;
	this->_logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	this->_logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	this->_logfd << "] [ " << title << " ] - Matt_daemon: " << info << ": ";
	this->_logfd <<  buff << std::endl;
}
