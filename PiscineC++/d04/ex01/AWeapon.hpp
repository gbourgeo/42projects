// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AWeapon.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 11:16:44 by root              #+#    #+#             //
//   Updated: 2018/07/04 11:43:50 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AWEAPON_HPP
# define AWEAPON_HPP

#include <string>

class AWeapon
{
public:
	AWeapon(std::string const & name, int apcost, int damage);
	AWeapon(AWeapon const & src);
	AWeapon &operator=(AWeapon const & rhs);
	virtual ~AWeapon();

	std::string		getName() const;
	int				getAPCost() const;
	int				getDamage() const;

	virtual void	attack() const = 0;

protected:
	AWeapon();

	std::string		_name;
	int				_apcost;
	int				_damage;
};

#endif
