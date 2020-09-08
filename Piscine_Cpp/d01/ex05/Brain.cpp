// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Brain.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 15:33:30 by root              #+#    #+#             //
//   Updated: 2018/06/29 16:01:39 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <sstream>
#include "Brain.hpp"

Brain::Brain()
{}

Brain::~Brain()
{}

std::string Brain::identify() const
{
	std::stringstream	ss;

	ss << (void *)this;
	return ss.str();
}
