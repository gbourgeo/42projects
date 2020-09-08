// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Human.cpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 19:10:22 by root              #+#    #+#             //
//   Updated: 2018/06/29 19:48:19 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Human.hpp"

void Human::meleeAttack(std::string const & target)
{
	std::cout << "Human MELEE attack " << target << std::endl;
}

void Human::rangedAttack(std::string const & target)
{
	std::cout << "Human RANGED attack " << target << std::endl;
}

void Human::intimidatingShout(std::string const & target)
{
	std::cout << "Human INTIMIDATE " << target << std::endl;
}

void Human::action(std::string const & action_name, std::string const & target)
{
	static std::string		abilities[] = { "melee",
											"ranged",
											"shout" };
	static HumanActions		actions[] = { &Human::meleeAttack,
										  &Human::rangedAttack,
										  &Human::intimidatingShout };
	std::size_t				i = 0;

	while (i < sizeof(abilities) / sizeof(*abilities)) {
		if (abilities[i] == action_name) {
			callMemberFunction(*this, actions[i])(target);
//			(this->*actions[i])(target); // Works too
		}
		i++;
	}
}
