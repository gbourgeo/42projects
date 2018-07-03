// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   FragTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 11:39:28 by root              #+#    #+#             //
//   Updated: 2018/07/03 14:51:07 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "FragTrap.hpp"

FragTrap::FragTrap(std::string &name): _hit(100), _maxHit(100), _energy(100),
										_maxEnergy(100), _level(1), _name(name),
										_meleeDamage(30), _rangedDamage(20), _armor(5)
{
	std::string quotes[] = { "01010110 01001001 01010110 01000001 00100000 01001100 01000001",
							 "We are the claptraps and we are legion! Viva la Robolution!",
							 "Follow the soothing sound of my voice!",
							 "AAAAAAAAND OPENNNNNNN!!!!",
							 "Whenever you're ready, buddy" };
	int			i = 0;

	for (size_t j = 0; j < name.length(); j++) {
		if (name[j] % 2 == 0)
			i += name[j];
		else if (name[j] % 3 == 0)
			i *= name[j];
		else if (name[j] % 5 == 0)
			i /= name[j];
		else
			i -= name[j];
	}
	i = i % (sizeof(quotes) / sizeof(*quotes) - 1);
	std::cout << "FR4G-TP " << this->_name << ": ";
	std::cout << "\e[33;1m\"" << quotes[i] << "\"\e[0m" << std::endl;
	std::srand(std::time(NULL));
}

FragTrap::~FragTrap()
{
	std::string quotes[] = { "Dangit, I'm out!",
							 "I'll stop talking when I'm dead!",
							 "I'll die the way I lived: annoying!",
							 "This could've gone better!",
							 "I bet your mom could do better!" };
	int			i = 0;

	for (size_t j = 0; j < this->_name.length(); j++) {
		if (this->_name[j] % 2 == 0)
			i += this->_name[j];
		else if (this->_name[j] % 3 == 0)
			i *= this->_name[j];
		else if (this->_name[j] % 5 == 0)
			i /= this->_name[j];
		else
			i -= this->_name[j];
	}
	i = i % (sizeof(quotes) / sizeof(*quotes));
	std::cout << "FR4G-TP " << this->_name << ": ";
	std::cout << "\e[31;1m\"" << quotes[i] << "\"\e[0m" << std::endl;
}

FragTrap::FragTrap(FragTrap const & src)
{
	*this = src;
}

FragTrap & FragTrap::operator=(FragTrap const & rhs)
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

void FragTrap::rangedAttack(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " at range, causing " << this->_rangedDamage << " points of damage !";
	std::cout << std::endl;
}

void FragTrap::meleeAttack(std::string const & target)
{
	std::cout << "FR4G-TP " << this->_name << " attacks " << target;
	std::cout << " in melee, causing " << this->_meleeDamage << " points of damage !";
	std::cout << std::endl;
}

void FragTrap::takeDamage(unsigned int amount)
{
	std::cout << "FR4G-TP " << this->_name << " takes " << amount << " damages";
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

void FragTrap::beRepaired(unsigned int amount)
{
	std::cout << "FR4G-TP " << this->_name << " heals " << amount << " points.";
	std::cout << " highering his HP from " << this->_hit;
	this->_hit += amount;
	if (this->_hit > this->_maxHit)
		this->_hit = this->_maxHit;
	std::cout << " to " << this->_hit << " !" << std::endl;
}

void FragTrap::vaulthunter_dot_exe(std::string const & target)
{
	if (this->_energy < 25) {
		std::cout << "Crap, no more shots left!" << std::endl;
	} else {
		std::string quotes[] = { "You call yourself a badass?",
								 "Wow, did I really do that?",
								 "Is it dead? Can, can I open my eyes now?",
								 "I didn't panic! Nope, not me!",
								 "Not so tough after all!",
								 "One down, any other takers?",
								 "I have gaskets tougher than you!",
								 "That was me! I did that!",
								 "Like running over a bug!",
								 "That was a close one!",
								 "Don't tell me that wasn't awesome!",
								 "Ha ha ha! Suck it!",
								 "Wait, did I really do that?",
								 "Holy moly!" };
		int			i = std::rand() % (sizeof(quotes) / sizeof(*quotes));

		std::cout << "FR4G-TRAP " << this->_name << " attacks " << target << ": \e[34;1m\"" << quotes[i] << "\"\e[0m" << std::endl;
		this->_energy -= 25;
	}	
}

unsigned int FragTrap::getHit() const
{
	return this->_hit;
}

unsigned int FragTrap::getMaxHit() const
{
	return this->_maxHit;
}

unsigned int FragTrap::getEnergy() const
{
	return this->_energy;
}

unsigned int FragTrap::getMaxEnergy() const
{
	return this->_maxEnergy;
}

unsigned int FragTrap::getLevel() const
{
	return this->_level;
}

std::string FragTrap::getName() const
{
	return this->_name;
}

unsigned int FragTrap::getMeleeDamage() const
{
	return this->_meleeDamage;
}

unsigned int FragTrap::getRangedDamage() const
{
	return this->_rangedDamage;
}

unsigned int FragTrap::getArmor() const
{
	return this->_armor;
}
