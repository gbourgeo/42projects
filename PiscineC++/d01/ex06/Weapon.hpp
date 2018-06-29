// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Weapon.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 17:45:04 by root              #+#    #+#             //
//   Updated: 2018/06/29 18:12:24 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <string>

class Weapon
{
public:
	Weapon(std::string type);
	~Weapon();

	std::string const & getType();
	void				setType(std::string type);
	
private:
	std::string	_type;
};

#endif
