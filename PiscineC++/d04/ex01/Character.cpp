// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 12:13:50 by root              #+#    #+#             //
//   Updated: 2018/07/04 13:37:34 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Character.hpp"

Character::Character()
{}

Character::Character(std::string const & name): _name(name), _ap(40), _weapon(NULL)
{}

Character::Character(Character const & src)
{
	*this = src;
}

Character & Character::operator=(Character const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_ap = rhs.getAP();
		this->_weapon = rhs.getWeapon();
	}
	return *this;
}

Character::~Character()
{}

void Character::recoverAP()
{
	std::cout << this->_name << " recovers 10 AP" << std::endl;
	this->_ap += 10;
	if (this->_ap > 40)
		this->_ap = 40;
	std::cout << this->_name << " have now " << this->_ap << " AP" << std::endl;
}

void Character::equip(AWeapon *weapon)
{
	this->_weapon = weapon;
}

void Character::attack(Enemy *target)
{
	if (this->_weapon && target && target->getHP() > 0) {
		if (this->_ap >= this->_weapon->getAPCost()) {
			this->_ap -= this->_weapon->getAPCost();
			std::cout << this->_name << " attacks " << target->getType() << " with a " << this->_weapon->getName() << std::endl; 
			this->_weapon->attack();
			target->takeDamage(this->_weapon->getDamage());
			if (target->getHP() <= 0) {
				delete target;
				std::cout << target->getType() << " deleted." << std::endl;
				target = NULL;
			}
		}
	}
}

std::string Character::getName() const
{
	return this->_name;
}

int Character::getAP() const
{
	return this->_ap;
}

AWeapon * Character::getWeapon() const
{
	return this->_weapon;
}

std::ostream & operator<<(std::ostream & os, const Character & src)
{
	os << src.getName() << " has " << src.getAP() << " AP and ";
	if (src.getWeapon())
		os << "wields a " << src.getWeapon()->getName() << std::endl;
	else
		os << "is unarmed" << std::endl;
	return os;
}
