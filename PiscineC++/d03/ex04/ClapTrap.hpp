// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ClapTrap.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 16:40:34 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:19:44 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <string>

class ClapTrap
{
public:
	ClapTrap();
	ClapTrap(std::string &name);
	ClapTrap(unsigned int hit, unsigned int maxHit, unsigned int energy,
			 unsigned int maxEnergy, unsigned int level, std::string &name,
			 unsigned int meleeDamage, unsigned int rangedDamage,
			 unsigned int armor);
	ClapTrap(ClapTrap const & src);
	ClapTrap &operator=(ClapTrap const & rhs);
	~ClapTrap();

	void			rangedAttack(std::string const & target);
	void			meleeAttack(std::string const & target);
	void			takeDamage(unsigned int amount);
	void			beRepaired(unsigned int amount);

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
