// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   FragTrap.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 11:23:12 by root              #+#    #+#             //
//   Updated: 2018/07/03 13:39:14 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include <string>

class FragTrap {
public:
	FragTrap(std::string &name);
	~FragTrap();
	FragTrap(FragTrap const & src);
	FragTrap & operator=(FragTrap const & rhs);

	void			rangedAttack(std::string const & target);
	void			meleeAttack(std::string const & target);
	void			takeDamage(unsigned int amount);
	void			beRepaired(unsigned int amount);
	void			vaulthunter_dot_exe(std::string const & target);

	unsigned int	getHit() const;
	unsigned int	getMaxHit() const;
	unsigned int	getEnergy() const;
	unsigned int	getMaxEnergy() const;
	unsigned int	getLevel() const;
	std::string		getName() const;
	unsigned int	getMeleeDamage() const;
	unsigned int	getRangedDamage() const;
	unsigned int	getArmor() const;

protected:
	unsigned int	_hit;
	unsigned int	_maxHit;
	unsigned int	_energy;
	unsigned int	_maxEnergy;
	unsigned int	_level;
	std::string		_name;
	unsigned int	_meleeDamage;
	unsigned int	_rangedDamage;
	unsigned int	_armor;
};

#endif
