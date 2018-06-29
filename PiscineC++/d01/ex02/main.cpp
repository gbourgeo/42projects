// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 12:57:52 by root              #+#    #+#             //
//   Updated: 2018/06/29 14:30:29 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include "ZombieEvent.hpp"

static Zombie	*randomChump()
{
	static std::string	names[] = { "Chloé", "Matthias", "Aurélien", "Aurélie",
									"Matthieu", "David", "Camille", "Gaetan" };

	return new Zombie(std::string("Basic"), names[std::rand() % (sizeof(names) / sizeof(*names))]);
}

int		main()
{
	ZombieEvent	zevent;
	Zombie		*zombies[8];
	Zombie		boss(std::string("Boss"), std::string("Carlos"));
	int			i;

	boss.announce();
	zevent.setZombieType(std::string("General"));
	zombies[0] = zevent.newZombie("Diana");
	zombies[0]->announce();
	zevent.setZombieType(std::string("Lieutenant"));
	zombies[1] = zevent.newZombie("Carlos");
	zombies[1]->announce();
	zombies[2] = zevent.newZombie("Hector");
	zombies[2]->announce();
	i = 3;
	std::srand(time(NULL));
	while (i < 8) {
		zombies[i] = randomChump();
		zombies[i]->announce();
		i++;
	}
	i = 8;
	while (i--) {
		delete zombies[i];
	}
	return 0;
}
