// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   SuperTrap.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 11:23:12 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:28:44 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SUPERTRAP_HPP
# define SUPERTRAP_HPP

#include <string>
#include "FragTrap.hpp"
#include "NinjaTrap.hpp"

class SuperTrap: public FragTrap, public NinjaTrap
{
public:
	SuperTrap();
	SuperTrap(std::string &name);
	~SuperTrap();
	SuperTrap(SuperTrap const & src);
	SuperTrap & operator=(SuperTrap const & rhs);

	void		rangedAttack(std::string const & target);
	void		meleeAttack(std::string const & target);
};

#endif
