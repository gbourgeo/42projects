// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ScavTrap.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 11:39:28 by root              #+#    #+#             //
//   Updated: 2018/07/03 21:43:04 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string &name): ClapTrap(100, 100, 50, 50, 1, name, 20, 15, 3)
{
	std::string quotes[] = { "ANARCHY FOREVERRRR!!! AND EVERRRR!!!",
							 "Booting sequence complete. Hello! I am your new steward bot. Designation: CL4P-TP, Hyperion Robot, Class C. Please adjust factory settings to meet your needs before deployment.",
							 "O-KAY! Thanks for giving me a second chance, God. I really appreciate it.",
							 "Hey everybody! Check out my package!",
							 "Let's get this party started!",
							 "Recompiling my combat code!",
							 "This time it'll be awesome, I promise!",
							 "Look out everybody! Things are about to get awesome!" };
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
	std::cout << "SC4V-TP " << this->_name << ": ";
	std::cout << "\e[33;1m\"" << quotes[i] << "\"\e[0m" << std::endl;
	std::srand(std::time(NULL));
}

ScavTrap::~ScavTrap()
{
	std::string quotes[] = { "I'm leaking!",
							 "You can't kill me!",
							 "I'm too pretty to die!",
							 "Crap!",
							 "Robot down!",
							 "No, nononono NO!",
							 "I'll never go back to the bad place!",
							 "I have many regrets!",
							 "Poop.",
							 "I'll get you next time!",
							 "No fair! I wasn't ready.",
							 "You got me!",
							 "Argh arghargh death gurgle gurglegurgle urgh... death.",
							 "Oh well.",
							 "Crap happens." };
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
	std::cout << "SC4V-TP " << this->_name << ": ";
	std::cout << "\e[31;1m\"" << quotes[i] << "\"\e[0m";
}

ScavTrap::ScavTrap(ScavTrap const & src)
{
	*this = src;
}

ScavTrap & ScavTrap::operator=(ScavTrap const & rhs)
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

void ScavTrap::challengeNewcomer(std::string const & target)
{
	if (this->_energy < 25) {
		std::cout << "Dangit, I'm out!" << std::endl;
	} else {
		std::string challenges[] = { "Yu-Gi-Ho! battle",
									 "eating frogs contest",
									 "spelling words backwards",
									 "rap",
									 "ice bucket" };
		std::string quotes[] = { "Badass!",
								 "Badass?! Aaahhh!",
								 "Look out, a Badass!",
								 "RUN FOR YOUR LIIIIIVES!!!",
								 "Oh, he's big... REALLY big!",
								 "Scary Badass dude, over there!",
								 "Oh no, Badass!",
								 "Save me from the Badass!",
								 "Psst! Ad-ass-bay, over ere-bay!",
								 "That guy looks an awful lot like a Badass!" };
		int			i = std::rand() % (sizeof(quotes) / sizeof(*quotes));
		int			j = (i * 12) % (sizeof(challenges) / sizeof(*challenges));

		std::cout << "SC4V-TRAP " << this->_name << " challenges " << target;
		std::cout << " to a \"" << challenges[j] << "\" contest: \e[34;1m\"";
		std::cout << quotes[i] << "\"\e[0m" << std::endl;
		this->_energy -= 25;
	}	
}
