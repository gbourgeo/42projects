// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   NinjaTrap.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/03 17:30:06 by root              #+#    #+#             //
//   Updated: 2018/07/03 22:22:38 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef NINJATRAP_HPP
# define NINJATRAP_HPP

# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"

class NinjaTrap: virtual public ClapTrap
{

public:
	NinjaTrap();
	NinjaTrap(std::string &name);
	NinjaTrap(NinjaTrap const & src);
	NinjaTrap &operator=(NinjaTrap const & rhs);
	~NinjaTrap();

	void		ninjaShoebox(ClapTrap & target);
	void		ninjaShoebox(FragTrap & target);
	void		ninjaShoebox(ScavTrap & target);
	void		ninjaShoebox(NinjaTrap & target);
};

#endif
