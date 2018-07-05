// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 10:50:59 by root              #+#    #+#             //
//   Updated: 2018/07/04 11:02:53 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Sorcerer.hpp"
#include "Peon.hpp"
#include "Victim.hpp"

int main()
{
	{
		Sorcerer	robert("Robert", "the Magnificient");
		
		Victim		jim("Jimmy");
		Peon		joe("Joe");
		
		std::cout << robert << jim << joe;
		
		robert.polymorph(jim);
		robert.polymorph(joe);
	}
	{
		Victim joe("Joe");
		Victim sarah = joe;
		Victim bob(sarah);

		std::cout << joe << sarah << bob;
		joe.getPolymorphed();
		sarah.getPolymorphed();
		bob.getPolymorphed();

		Peon pepe("Pepe");
		Peon carl = pepe;
		Peon martin(carl);
		Victim bobby = martin;
		Victim sar(carl);

		std::cout << pepe << carl << martin << bobby << sar;
	}
	return 0;
}
