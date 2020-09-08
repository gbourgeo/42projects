// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ZombieHorde.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 13:03:24 by root              #+#    #+#             //
//   Updated: 2018/06/29 14:35:04 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <string>
#include <ctime>
#include <cstdlib>
#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(int N): _N(N)
{
	static std::string	names[] = { "Chloé", "Matthias", "Aurélien", "Aurélie",
									"Matthieu", "David", "Camille", "Gaetan" };
	int					i;

	_zombies = NULL;
	if (N <= 0)
		return ;
	_zombies = new Zombie[N];
	std::srand(std::time(NULL));
	i = 0;
	while (i < N) {
		_zombies[i].type = std::string("Horde member");
		_zombies[i].name = names[std::rand() % (sizeof(names) / sizeof(*names))];
		i++;
	}
}

ZombieHorde::~ZombieHorde()
{
	delete [] _zombies;
}

void ZombieHorde::announce()
{
	int		i = 0;

	while (i < _N) {
		_zombies[i].announce();
		i++;
	}
}
