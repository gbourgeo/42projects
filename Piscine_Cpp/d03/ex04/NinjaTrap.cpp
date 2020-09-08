// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NinjaTrap.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 17:30:38 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:22:58 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <iostream>
#include "NinjaTrap.hpp"

NinjaTrap::NinjaTrap(): ClapTrap()
{}

NinjaTrap::NinjaTrap(std::string &name): ClapTrap(60, 60, 120, 120, 1, name, 60, 5, 0)
{
	std::cout << "\e[33;1m\"NINJA !\"\e[0m" << std::endl;
}

NinjaTrap::NinjaTrap(NinjaTrap const & src)
{
	*this = src;
}

NinjaTrap &NinjaTrap::operator=(NinjaTrap const & rhs)
{
	if (this != &rhs)
	{
		this->_hit = rhs.getHit();
		this->_maxHit = rhs.getMaxHit();
		this->_energy = rhs.getEnergy();
		this->_maxEnergy = rhs.getMaxEnergy();
		this->_level = rhs.getLevel();
		this->_name = rhs.getName();
		this->_meleeDamage = rhs.getMeleeDamage();
		this->_rangedDamage = rhs.getRangedDamage();
		this->_armor = rhs.getArmor();
	}
	return *this;
}

NinjaTrap::~NinjaTrap()
{
	std::cout << "\e[31;1m\"NINJA !\"\e[0m";
}

void NinjaTrap::ninjaShoebox(ClapTrap & target)
{
	std::string object[] = { "shoe", "towel", "lipstick" };
	size_t		i = 0;

	i = rand() * 12;
	i = (i / 3) % (sizeof(object) / sizeof(*object));
	std::cout << "The weather is cold, the night brings the first deadly shadow and in a loud silence ";
	std::cout << this->_name << " grabs his/her " << object[i] << " and throw it to ";
	std::cout << target.getName() << ". He/she disappeared in a loud laught, letting ";
	std::cout << target.getName() << " in a deep misunderstanding..." << std::endl;
}

void NinjaTrap::ninjaShoebox(FragTrap & target)
{
	std::string object[] = { "sword", "knife", "shuriken" };
	size_t		i = 0;

	i = rand() * 12;
	i = (i / 3) % (sizeof(object) / sizeof(*object));
	std::cout << "The weather is cold, the night brings her first shadow and in a dead silence ";
	std::cout << this->_name << " grabs his/her " << object[i] << " and gave it to ";
	std::cout << target.getName() << "." << std::endl;
}

void NinjaTrap::ninjaShoebox(ScavTrap & target)
{
	std::string object[] = { "rock", "paper", "scissor" };
	size_t		i = 0;
	size_t		j = 0;

	i = rand() * 12;
	j = rand() * 7;
	i = (i / 3) % (sizeof(object) / sizeof(*object));
	j = (j * 13) % (sizeof(object) / sizeof(*object));
	std::cout << "The weather is cold, the night brings her first shadow and in a dead silence.";
	std::cout << this->_name << " dares " << target.getName() << " to a rock/paper/scissor game..." << std::endl;
	std::cout << this->_name << " showed " << object[i] << ", ";
	std::cout << target.getName() << " showed " << object[j] << "." << std::endl;
	std::cout << target.getName() << " died." << std::endl;
}

void NinjaTrap::ninjaShoebox(NinjaTrap & target)
{
	std::cout << "Hi " << target.getName() << " !" << std::endl;
	std::cout << "Hello " << this->_name << " !" << std::endl;
}
