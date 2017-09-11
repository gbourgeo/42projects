// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:46:49 by root              #+#    #+#             //
//   Updated: 2017/09/11 06:31:45 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Tintin.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

Tintin_reporter::Tintin_reporter()
{
	mkdir(LOG_DIR, 0600);
	logfd.open(LOG_FILE, std::ofstream::out | std::ofstream::app);
	if (logfd.is_open())
		log("INFO", "Started.");
	else
		_exit(1);
}

Tintin_reporter::Tintin_reporter(const Tintin_reporter & rhs)
{
	*this = rhs;
}

Tintin_reporter::~Tintin_reporter()
{
	if (logfd.is_open())
		logfd.close();
}

Tintin_reporter & Tintin_reporter::operator=(Tintin_reporter const & rhs)
{
	(void)rhs;
	return *this;
}

int Tintin_reporter::log(const char *title, const char *info)
{
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	logfd << "] [ " << title << " ] - Matt_daemon: " << info << std::endl;
	return 1;
}

int Tintin_reporter::log(const char *title, const char *info, pid_t pid)
{
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	logfd << "] [ " << title << " ] - Matt_daemon: " << info;
	logfd << pid << std::endl;
	return 1;
}

int Tintin_reporter::log(const char *title, const char *info, char *buff)
{
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	logfd << "[" << tm->tm_mday << "/" << tm->tm_mon << "/" << 1900 + tm->tm_year;
	logfd << "-" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec;
	logfd << "] [ " << title << " ] - Matt_daemon: " << info;
	logfd <<  buff << std::endl;
	return 1;

}
