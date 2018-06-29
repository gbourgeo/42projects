// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 21:15:09 by root              #+#    #+#             //
//   Updated: 2018/06/29 21:24:01 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Logger.hpp"

int main()
{
	std::string	buff;
	Logger		log("logfile.log");

	while (getline(std::cin, buff))
	{
		log.log("console", buff);
		log.log("file", buff);
	}
}
