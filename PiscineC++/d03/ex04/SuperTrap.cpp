// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperTrap.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 11:39:28 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:35:38 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "SuperTrap.hpp"

SuperTrap::SuperTrap(): ClapTrap()
{
	this->_hit = 100;
	this->_maxHit = 100;
	this->_energy = 120;
	this->_maxEnergy = 120;
	this->_level = 1;
	this->_name = "SuperV";
	this->_meleeDamage = 60;
	this->_rangedDamage = 20;
	this->_armor = 5;
	std::cout << "\e[33;1m\"SuperTraps !!! SuperTraps !!! SuperTraps !!!\"\e[0m" << std::endl;
}

SuperTrap::SuperTrap(std::string &name): ClapTrap(name)
{
	this->_hit = 100;
	this->_maxHit = 100;
	this->_energy = 120;
	this->_maxEnergy = 120;
	this->_level = 1;
	this->_name = name;
	this->_meleeDamage = 60;
	this->_rangedDamage = 20;
	this->_armor = 5;
	std::cout << "\e[33;1m\"SuperTraps !!! SuperTraps !!! SuperTraps !!!\"\e[0m" << std::endl;
}

SuperTrap::~SuperTrap()
{
	std::cout << "\e[31;1m\"Yipikayeah !\"\e[0m";
}

SuperTrap::SuperTrap(SuperTrap const & src)
{
	*this = src;
}

SuperTrap & SuperTrap::operator=(SuperTrap const & rhs)
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

void SuperTrap::rangedAttack(std::string const & target)
{
	FragTrap::rangedAttack(target);
}

void SuperTrap::meleeAttack(std::string const & target)
{
	NinjaTrap::meleeAttack(target);
}
