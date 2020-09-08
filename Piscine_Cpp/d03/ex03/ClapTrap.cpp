// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ClapTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 16:40:21 by root              #+#    #+#             //
//   Updated: 2018/07/03 17:21:43 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): _hit(0), _maxHit(0), _energy(0), _maxEnergy(0), _level(0),
					  _name(""), _meleeDamage(0), _rangedDamage(0), _armor(0)
{
	std::cout << "A new CL4P-TP with no name is born ! " << std::endl;
}

ClapTrap::ClapTrap(unsigned int hit, unsigned int maxHit, unsigned int energy,
				   unsigned int maxEnergy, unsigned int level, std::string &name,
				   unsigned int meleeDamage, unsigned int rangedDamage,
				   unsigned int armor):
	_hit(hit), _maxHit(maxHit), _energy(energy), _maxEnergy(maxEnergy), _level(level),
	_name(name), _meleeDamage(meleeDamage), _rangedDamage(rangedDamage), _armor(armor)
{
	std::cout << "A new CL4P-TP is born ! His name is " << this->_name;
	std::cout << ". Lets hear his first words: ";
}

ClapTrap::ClapTrap(ClapTrap const & src)
{
	*this = src;
}

ClapTrap & ClapTrap::operator=(ClapTrap const & rhs)
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

ClapTrap::~ClapTrap()
{
	std::cout << " " << this->_name << " said before he/she died." << std::endl;
}

void ClapTrap::rangedAttack(std::string const & target)
{
	std::cout << "CL4P-TP " << this->_name << " attacks " << target;
	std::cout << " at range, causing " << this->_rangedDamage << " points of damage !";
	std::cout << std::endl;
}

void ClapTrap::meleeAttack(std::string const & target)
{
	std::cout << "CL4P-TP " << this->_name << " attacks " << target;
	std::cout << " in melee, causing " << this->_meleeDamage << " points of damage !";
	std::cout << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "CL4P-TP " << this->_name << " takes " << amount << " damages";
	if (amount > this->_armor) {
		amount -= this->_armor;
		this->_armor = 0;
		if (this->_hit < amount)
			this->_hit = 0;
		else
			this->_hit -= amount;
	} else {
		this->_armor -= amount;
	}
	std::cout << ", lowering his HP to " << this->_hit << " and his ARMOR to " << this->_armor;
	std::cout << " !" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "CL4P-TP " << this->_name << " heals " << amount << " points.";
	std::cout << " highering his HP from " << this->_hit;
	this->_hit += amount;
	if (this->_hit > this->_maxHit)
		this->_hit = this->_maxHit;
	std::cout << " to " << this->_hit << " !" << std::endl;
}

unsigned int ClapTrap::getHit() const
{
	return this->_hit;
}

unsigned int ClapTrap::getMaxHit() const
{
	return this->_maxHit;
}

unsigned int ClapTrap::getEnergy() const
{
	return this->_energy;
}

unsigned int ClapTrap::getMaxEnergy() const
{
	return this->_maxEnergy;
}

unsigned int ClapTrap::getLevel() const
{
	return this->_level;
}

std::string ClapTrap::getName() const
{
	return this->_name;
}

unsigned int ClapTrap::getMeleeDamage() const
{
	return this->_meleeDamage;
}

unsigned int ClapTrap::getRangedDamage() const
{
	return this->_rangedDamage;
}

unsigned int ClapTrap::getArmor() const
{
	return this->_armor;
}
