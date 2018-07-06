// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 10:36:12 by root              #+#    #+#             //
//   Updated: 2018/07/05 22:40:17 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"

int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	src->learnMateria(0);
	src->learnMateria(new Ice());
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* zaz = new Character("zaz");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	zaz->equip(tmp);
	tmp = src->createMateria("cure");
	zaz->equip(tmp);
	tmp = src->createMateria("fire");
	zaz->equip(tmp);

	ICharacter* bob = new Character("bob");

	zaz->use(-1, *bob);
	zaz->use(0, *bob);
	zaz->use(1, *bob);
	zaz->use(2, *bob);
	zaz->use(3, *bob);
	zaz->use(4, *bob);
	zaz->use(42, *bob);

	std::cout << std::endl;
	zaz->unequip(-1);
	zaz->unequip(0);
	zaz->unequip(1);
	zaz->unequip(2);
	zaz->unequip(3);
	zaz->unequip(4);

	tmp = src->createMateria("cure");
	zaz->equip(tmp);
	tmp = src->createMateria("water");
	zaz->equip(tmp);
	tmp = src->createMateria("fire");
	zaz->equip(tmp);
	tmp = src->createMateria("ice");
	zaz->equip(tmp);
	tmp = src->createMateria("ice");
	zaz->equip(tmp);
	tmp = src->createMateria("ice");
	zaz->equip(tmp);
	tmp = src->createMateria("ice");
	zaz->equip(tmp);
	tmp = src->createMateria("ice");
	zaz->equip(tmp);

	zaz->use(-1, *bob);
	zaz->use(0, *bob);
	zaz->use(1, *bob);
	zaz->use(2, *bob);
	zaz->use(3, *bob);
	zaz->use(4, *bob);
	zaz->use(42, *bob);

	delete bob;
	delete zaz;
	delete src;
	return 0;
}
