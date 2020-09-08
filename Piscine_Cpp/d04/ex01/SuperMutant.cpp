// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperMutant.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 12:01:01 by root              #+#    #+#             //
//   Updated: 2018/07/04 12:13:06 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "SuperMutant.hpp"

SuperMutant::SuperMutant(): Enemy(170, "Super Mutant")
{
	std::cout << "Gaaah. Me want smash heads !" << std::endl;
}

SuperMutant::~SuperMutant()
{
	std::cout << "Aaaargh..." << std::endl;
}

SuperMutant::SuperMutant(SuperMutant const & src)
{
	*this = src;
}

SuperMutant & SuperMutant::operator=(SuperMutant const & rhs)
{
	if (this != &rhs)
	{
		this->_hp = rhs.getHP();
		this->_type = rhs.getType();
	}
	return *this;
}

void SuperMutant::takeDamage(int damage)
{
	if (damage > 3)
		Enemy::takeDamage(damage - 3);
}
