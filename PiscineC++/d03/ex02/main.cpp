// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 12:02:50 by root              #+#    #+#             //
//   Updated: 2018/07/03 17:14:42 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <ctime>
#include <iostream>
#include <cstdlib>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	std::string	names[] = { "Joey", "John", "Maria", "Kevin", "Andy", "Marie" };
	size_t		nb = sizeof(names) / sizeof(*names) - 1;
	FragTrap	*frag[nb + 1];
	

	std::srand(std::time(NULL));
	for (size_t i = 0; i < nb + 1; i++) {
		frag[i] = new FragTrap(names[i]);
	}

	for (size_t i = 0, j; i < nb + 1; i++) {
		j = std::rand();
		frag[i]->rangedAttack(names[((j * 2) / 3) % nb]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb + 1; i++) {
		j = std::rand();
		frag[i]->meleeAttack(names[((j * 2) / 3) % nb]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb + 1; i++) {
		j = std::rand();
		frag[i]->takeDamage(((j * 2) / 4) % 50);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb + 1; i++) {
		j = std::rand();
		frag[i]->beRepaired(((j * 2) / 4) % 50);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb + 1; i++) {
		j = std::rand();
		frag[i]->vaulthunter_dot_exe(names[((j * 2) / 4) % nb]);
	}

	std::string		snames[] = { "Suzanne", "Henry", "Clara", "Steven", "Amy", "Cassandra", "Colin" };
	size_t			nb2 = sizeof(snames) / sizeof(*snames) - 1;
	ScavTrap		*trap[nb2 + 1];

	std::cout << std::endl;
	for (size_t i = 0; i < nb2 + 1; i++) {
		trap[i] = new ScavTrap(snames[i]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb2 + 1; i++) {
		j = std::rand();
		trap[i]->rangedAttack(names[((j * 2) / 3) % nb]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb2 + 1; i++) {
		j = std::rand();
		trap[i]->meleeAttack(names[((j * 2) / 3) % nb]);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb2 + 1; i++) {
		j = std::rand();
		trap[i]->takeDamage(((j * 2) / 4) % 50);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb2 + 1; i++) {
		j = std::rand();
		trap[i]->beRepaired(((j * 2) / 4) % 50);
	}
	std::cout << std::endl;
	for (size_t i = 0, j; i < nb2 + 1; i++) {
		j = std::rand();
		trap[i]->challengeNewcomer(names[((j * 2) / 3) % nb]);
	}

	std::cout << std::endl;
	for (size_t i = 0; i < nb + 1; i++) {
		delete frag[i];
	}
	std::cout << std::endl;
	for (size_t i = 0; i < nb2 + 1; i++) {
		delete trap[i];
	}
	return 0;
}
