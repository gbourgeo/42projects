// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tintin.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/10 19:47:05 by root              #+#    #+#             //
//   Updated: 2017/09/11 06:23:04 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TINTIN_HPP
# define TINTIN_HPP

# define LOG_DIR	"/var/log/matt_daemon/"
# define LOG_FILE	"/var/log/matt_daemon/matt_daemon.log"

#include <iostream>
#include <fstream>

class			Tintin_reporter
{

public:
	Tintin_reporter();
	Tintin_reporter(const Tintin_reporter & rhs);
	~Tintin_reporter();
	Tintin_reporter & operator=(Tintin_reporter const & rhs);

	int		log(const char *title, const char *info);
	int		log(const char *title, const char *info, pid_t pid);
	int		log(const char *title, const char *info, char *buff);

	std::ofstream	logfd;
};

#endif
