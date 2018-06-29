// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HumanA.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 17:51:31 by root              #+#    #+#             //
//   Updated: 2018/06/29 18:06:55 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon & weapon): _weapon(weapon), _name(name)
{}

HumanA::~HumanA()
{}

void HumanA::attack()
{
	std::cout << _name << " attack with his " << _weapon.getType() << std::endl;
}
