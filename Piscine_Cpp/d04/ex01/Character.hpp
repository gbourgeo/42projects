// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Character.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 12:13:29 by root              #+#    #+#             //
//   Updated: 2018/07/04 12:41:31 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include <iostream>
#include <string>
#include "AWeapon.hpp"
#include "Enemy.hpp"

class Character
{
public:
	Character(std::string const & name);
	Character(Character const & src);
	Character & operator=(Character const & rhs);
	~Character();

	void			recoverAP();
	void			equip(AWeapon *);
	void			attack(Enemy *);
	std::string		getName() const;
	int				getAP() const;
	AWeapon			* getWeapon() const;

private:
	Character();
	std::string		_name;
	int				_ap;
	AWeapon			*_weapon;
};

std::ostream & operator<<(std::ostream & os, const Character & src);

#endif
