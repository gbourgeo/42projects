// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 10:23:00 by root              #+#    #+#             //
//   Updated: 2018/07/05 10:35:31 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "TacticalMarine.hpp"
#include "AssaultTerminator.hpp"
#include "Squad.hpp"

int main()
{
	ISpaceMarine *bob = new TacticalMarine;
	ISpaceMarine *jim = new AssaultTerminator;

	ISquad *vlc = new Squad;

	vlc->push(bob);
	vlc->push(jim);

	vlc->push(bob);
	vlc->push(jim);
	vlc->push(0);
	for (int i = 0; i < vlc->getCount(); i++)
	{
		ISpaceMarine* cur = vlc->getUnit(i);
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}

	ISpaceMarine* cur = vlc->getUnit(-1);
	if (cur) {
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}

	cur = vlc->getUnit(2);
	if (cur) {
		cur->battleCry();
		cur->rangedAttack();
		cur->meleeAttack();
	}

	delete vlc;	
	return 0;
}
