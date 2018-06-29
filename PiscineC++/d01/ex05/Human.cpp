// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Human.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 15:37:05 by root              #+#    #+#             //
//   Updated: 2018/06/29 15:50:24 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Human.hpp"

Human::Human()
{}

Human::~Human()
{}

std::string Human::identify() const
{
	return _brain.identify();
}

const Brain & Human::getBrain()
{
	return _brain;
}
