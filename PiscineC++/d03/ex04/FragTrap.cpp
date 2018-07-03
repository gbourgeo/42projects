// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   FragTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 11:39:28 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:36:38 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{}

FragTrap::FragTrap(std::string &name): ClapTrap(100, 100, 100, 100, 1, name, 30, 20, 5)
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
	std::cout << "\e[31;1m\"" << quotes[i] << "\"\e[0m";
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
