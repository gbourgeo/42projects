// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Daemon.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/08 00:38:29 by root              #+#    #+#             //
//   Updated: 2017/09/11 18:38:25 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Daemon.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

Daemon::Daemon(void)
{
	struct stat	buf;

	if (stat(LOCK_FILE, &buf) == 0)
		return ;
	d_pid = getpid();
	d_lockfd.open(LOCK_FILE, std::ostream::out | std::ostream::trunc);
	if (d_lockfd.is_open())
		log("INFO", "Daemon started. PID: ", d_pid);
}

Daemon::Daemon(Daemon const & src)
{
	*this = src;
}

Daemon::~Daemon(void)
{
	if (d_lockfd.is_open())
		d_lockfd.close();
	remove(LOCK_FILE);
}

Daemon & Daemon::operator=(Daemon const & rhs)
{
	(void)rhs;
	return *this;
}

int	Daemon::getPid(void) const
{
	return this->d_pid;
}

bool Daemon::isLocked(void) const
{
	return this->d_lockfd.is_open();
}

bool Daemon::isLogOpen(void) const
{
	return tintin.logfd.is_open();
}

int Daemon::getServfd( void ) const
{
	return server.getServfd();
}

const char *Daemon::getServerError(void) const
{
	return server.getError();
}

int		Daemon::log(const char *title, const char *info)
{
	return tintin.log(title, info);
}

int		Daemon::log(const char *title, const char *info, pid_t pid)
{
	return tintin.log(title, info, pid);
}

int		Daemon::log(const char *title, const char *info, char *buff)
{
	return tintin.log(title, info, buff);
}

void	Daemon::setSignalsHandler(void) const
{
	int	i;

	i = 0;
	while (i < _NSIG)
	{
		signal(i++, signalsHandler);
	}
}

int		Daemon::signalsHandler(int sig)
{
	
}
