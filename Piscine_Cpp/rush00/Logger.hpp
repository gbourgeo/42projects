/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 12:37:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 15:21:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
 #define LOGGER_HPP

# include <string>
# include <fstream>

class Logger
{
public:
	Logger(std::string filename);
	~Logger(void);

	void			log(const char *format, ...);

	std::string		getFilename(void) const;


private:
	Logger();
	std::string		formatLogDate(void);

	// Property
	std::ofstream	_myfile;
	std::string		_filename;
};

static Logger			logger("default.log");

#endif