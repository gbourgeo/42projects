// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:47:05 by root              #+#    #+#             //
//   Updated: 2017/09/27 23:48:00 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TINTIN_HPP
# define TINTIN_HPP

# define LOG_DIR	"/var/log/matt_daemon/"
# define LOG_FILE	"/var/log/matt_daemon/matt_daemon.log"

# include <iostream>
# include <fstream>

class			Tintin_reporter
{

public:
	Tintin_reporter();
	Tintin_reporter(const Tintin_reporter & rhs);
	~Tintin_reporter();
	Tintin_reporter & operator=(Tintin_reporter const & rhs);
	
	void	log(const char *title, const char *info);
	void	log(const char *title, const char *info, pid_t pid);
	void	log(const char *title, const char *info, const char *ip, const char *host, const char *port);
	void	log(const char *title, const char *info, const char *buff);
	void	log(const char *title, std::string info);

	std::ofstream	_logfd;

};

#endif
