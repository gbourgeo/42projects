// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 12:02:50 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:37:43 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <ctime>
#include <iostream>
#include <cstdlib>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"
#include "SuperTrap.hpp"

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

	std::string nname[] = {"Martin","Eric","Sylvie"};
	ClapTrap	clap;
	NinjaTrap	ninja1(nname[0]);
	NinjaTrap	ninja2(nname[1]);

	ninja1.rangedAttack(names[0]);
	ninja1.meleeAttack(names[1]);
	ninja1.takeDamage(100);
	ninja1.beRepaired(50);
	ninja1.ninjaShoebox(clap);
	ninja1.ninjaShoebox(*frag[0]);
	ninja1.ninjaShoebox(*trap[0]);
	ninja1.ninjaShoebox(ninja2);

	ninja2.rangedAttack(names[0]);
	ninja2.meleeAttack(names[1]);
	ninja2.takeDamage(100);
	ninja2.beRepaired(50);
	ninja2.ninjaShoebox(clap);
	ninja2.ninjaShoebox(*frag[0]);
	ninja2.ninjaShoebox(*trap[0]);
	ninja2.ninjaShoebox(ninja1);

	std::string willy("Willy");
	SuperTrap	toto(willy);

	toto.rangedAttack(nname[0]);
	toto.meleeAttack(nname[1]);
	toto.takeDamage(90);
	toto.beRepaired(10);
	
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
