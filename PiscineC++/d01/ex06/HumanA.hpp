// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HumanA.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 17:49:10 by root              #+#    #+#             //
//   Updated: 2018/06/29 18:06:09 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HUMANA_HPP
# define HUMANA_HPP

#include <string>
#include "Weapon.hpp"

class HumanA
{
public:
	HumanA(std::string name, Weapon & weapon);
	~HumanA();

	void		attack();
	
private:
	Weapon		&_weapon;
	std::string	_name;
};
	
#endif
