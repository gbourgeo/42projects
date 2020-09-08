// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 13:00:14 by root              #+#    #+#             //
//   Updated: 2018/06/29 14:31:12 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Zombie.hpp"

Zombie::Zombie()
{}

Zombie::Zombie(std::string type, std::string name):
	type(type),
	name(name)
{}

Zombie::~Zombie()
{
	std::cout << '<' << name << " (" << type << ")> Euuuuuuur..." << std::endl;
}

void Zombie::announce()
{
	std::cout << '<' << name << " (" << type << ")> Braiiiiiinnnssss..." << std::endl;
}
