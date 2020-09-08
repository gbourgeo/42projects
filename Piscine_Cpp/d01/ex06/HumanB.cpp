// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HumanB.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 17:51:31 by root              #+#    #+#             //
//   Updated: 2018/06/29 18:07:20 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "HumanB.hpp"

HumanB::HumanB(std::string name): _weapon(NULL), _name(name)
{}

HumanB::~HumanB()
{}

void HumanB::attack()
{
	if (_weapon)
		std::cout << _name << " attack with his " << _weapon->getType() << std::endl;
	else
		std::cout << _name << " attack with his... wait... where is his weapon ?" << std::endl;
}

void HumanB::setWeapon(Weapon & weapon)
{
	this->_weapon = &weapon;
}
