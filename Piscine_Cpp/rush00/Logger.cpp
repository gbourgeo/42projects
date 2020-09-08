/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 16:28:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 15:21:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

Logger::Logger()
{}

Logger::Logger(std::string filename)
{
	this->_filename = filename;
	if (this->_myfile.is_open() == false)
		this->_myfile.open(this->_filename, std::ios::app | std::ios::out);
}

Logger::~Logger(void)
{
	if (this->_myfile.is_open() == true)
		this->_myfile.close();
}

std::string		Logger::getFilename(void) const
{
	return this->_filename;
}

std::string			Logger::formatLogDate(void) {
	time_t			rawtime;
	struct tm		*timeinfo;
	char			buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);
	strftime (buffer, 80, "[%d-%m-%Y %H:%M:%S] ", timeinfo);
	return std::string(buffer);
}

void				Logger::log(const char *format, ...)
{
	va_list		va;
	int			i, j;
	std::string	buf;

	va_start(va, format);
	i = j = 0;
	buf.clear();
	while (format[i])
	{
		if (format[i] == '%')
		{
			buf.append(format + j, i - j);
			i++;
			if (format[i] == 'd')
			{
				int ret = va_arg(va, int);
				buf += std::to_string(ret);
			}
			else if (format[i] == 'l')
			{
				unsigned long ret = va_arg(va, unsigned long);
				buf += std::to_string(ret);
			}
			else if (format[i] == 'b')
			{
				double ret = va_arg(va, double);
				buf += std::to_string(ret);
			}
			else if (format[i] == 's')
			{
				char *ret = va_arg(va, char *);
				if (ret)
					buf.append(ret);
				else
					buf.append("(null)");
			}
			else if (format[i] == 'p')
			{
				unsigned long ret = va_arg(va, unsigned long);
				buf.append("0x");
				buf += std::to_string(ret);
			}
			else
				buf.append("%");
			j = i + 1;
		}
		i++;
	}
	buf.append(format + j, i - j);
	this->_myfile << this->formatLogDate() << buf;
	this->_myfile.flush();
	buf.clear();
	va_end(va);
}
