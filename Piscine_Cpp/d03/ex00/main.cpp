// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 12:02:50 by root              #+#    #+#             //
//   Updated: 2018/07/03 14:00:47 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <ctime>
#include <iostream>
#include <cstdlib>
#include "FragTrap.hpp"

int main()
{
	std::string	names[] = { "Joey", "John", "Maria", "Kevin", "Andy", "Marie",
							"Suzanne", "Henry", "Clara", "Steven", "Amy", "Cassandra", "Colin" };
	FragTrap	*frag[13];

	std::srand(std::time(NULL));
	for (size_t i = 0; i < 13; i++) {
		frag[i] = new FragTrap(names[i]);
	}

	for (size_t i = 0, j; i < 13; i++) {
		j = std::rand();
		frag[i]->rangedAttack(names[((j * 2) / 3) % 12]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < 13; i++) {
		j = std::rand();
		frag[i]->meleeAttack(names[((j * 2) / 3) % 12]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < 13; i++) {
		j = std::rand();
		frag[i]->takeDamage(((j * 2) / 4) % 50);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < 13; i++) {
		j = std::rand();
		frag[i]->beRepaired(((j * 2) / 4) % 50);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < 13; i++) {
		j = std::rand();
		frag[i]->vaulthunter_dot_exe(names[((j * 2) / 4) % 12]);
	}
	
	return 0;
}
