// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ZombieEvent.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 13:03:24 by root              #+#    #+#             //
//   Updated: 2018/06/29 13:54:19 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ZombieEvent.hpp"

ZombieEvent::ZombieEvent()
{}

ZombieEvent::~ZombieEvent()
{}

void ZombieEvent::setZombieType(std::string type)
{
	_type = type;
}

Zombie *ZombieEvent::newZombie(std::string name)
{
	return new Zombie(_type, name);
}
