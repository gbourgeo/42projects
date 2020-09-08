// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TacticalMarine.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 10:05:34 by root              #+#    #+#             //
//   Updated: 2018/07/05 10:15:53 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "TacticalMarine.hpp"

TacticalMarine::TacticalMarine()
{
	std::cout << "Tactical Marine ready for battle" << std::endl;
}

TacticalMarine::TacticalMarine(TacticalMarine const & src)
{
	*this = src;
}

TacticalMarine & TacticalMarine::operator=(TacticalMarine const & rhs)
{
	if (this != &rhs)
	{

	}
	return *this;
}

TacticalMarine::~TacticalMarine()
{
	std::cout << "Aaaargh..." << std::endl;
}

ISpaceMarine* TacticalMarine::clone() const
{
	TacticalMarine		*newMarine = new TacticalMarine(*this);

	return newMarine;
}

void TacticalMarine::battleCry() const
{
	std::cout << "For the holy PLOT !" << std::endl;
}

void TacticalMarine::rangedAttack() const
{
	std::cout << "* attacks with bolter *" << std::endl;
}

void TacticalMarine::meleeAttack() const
{
	std::cout << "* attacks with chainsword *" << std::endl;
}
