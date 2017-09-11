// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Daemon.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/14 23:45:23 by gbourgeo          #+#    #+#             //
//   Updated: 2017/09/11 18:37:31 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DAEMON_HPP
# define DAEMON_HPP

# include "Tintin.hpp"
# include "Server.hpp"

# define LOCK_FILE	"/var/lock/matt_daemon.lock"

# include <iostream>
# include <fstream>

class Daemon
{

public:
	Daemon(void);
	Daemon(const Daemon&);
	~Daemon(void);
	Daemon & operator=(Daemon const & rhs);

	void	setSignalsHandler(void) const;
	int		signalsHandler(int sig) const;
	int		getPid(void) const;
	bool	isLocked(void) const;
	bool	isLogOpen(void) const;
	int		getServfd(void) const;
	const char	*getServerError(void) const;
	int		log(const char *title, const char *info);
	int		log(const char *title, const char *info, pid_t pid);
	int		log(const char *title, const char *info, char *buff);
	
private:
	Tintin_reporter	tintin;
	Server			server;
	pid_t			d_pid;
	std::ofstream	d_lockfd;

};

#endif
