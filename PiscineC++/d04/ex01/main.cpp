// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 12:42:19 by root              #+#    #+#             //
//   Updated: 2018/07/04 13:38:01 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Character.hpp"
#include "RadScorpion.hpp"
#include "PlasmaRifle.hpp"
#include "PowerFist.hpp"
#include "SuperMutant.hpp"

int main()
{
	Character	*skaar = new Character("Skaar");

	std::cout << *skaar;

	Enemy		*b = new RadScorpion();
	std::cout << "A new " << b->getType() << " appeared !!! He has " << b->getHP() << " HP." << std::endl;

	AWeapon		*pr = new PlasmaRifle();
	AWeapon		*pf = new PowerFist();

	skaar->equip(pr);
	std::cout << *skaar;
	skaar->equip(pf);
	std::cout << *skaar;

	skaar->attack(b);
	std::cout << *skaar;
	std::cout << b->getType() << " has now " << b->getHP() << " HP." << std::endl;
	skaar->equip(pr);
	std::cout << *skaar;
	skaar->attack(b);
	std::cout << *skaar;
	std::cout << b->getType() << " has now " << b->getHP() << " HP." << std::endl;
	skaar->attack(b);
	std::cout << *skaar;
	std::cout << b->getType() << " has now " << b->getHP() << " HP." << std::endl;
	skaar->attack(b);
	std::cout << *skaar;
	std::cout << b->getType() << " has now " << b->getHP() << " HP." << std::endl;

	Enemy		*c = new SuperMutant();
	std::cout << "A new " << c->getType() << " appeared !!! He has " << c->getHP() << " HP." << std::endl;

	skaar->equip(NULL);
	std::cout << *skaar;

	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;

	skaar->equip(pr);
	std::cout << *skaar;
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->equip(pf);
	std::cout << *skaar;
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->recoverAP();
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->recoverAP();
	skaar->recoverAP();
	skaar->recoverAP();
	skaar->recoverAP();
	skaar->recoverAP();
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;
	skaar->attack(c);
	std::cout << *skaar;
	std::cout << c->getType() << " has now " << c->getHP() << " HP." << std::endl;

	return 0;
}
