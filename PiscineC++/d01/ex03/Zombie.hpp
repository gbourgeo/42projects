// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Zombie.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 12:58:25 by root              #+#    #+#             //
//   Updated: 2018/06/29 14:31:51 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>

class Zombie
{
public:
	Zombie();
	Zombie(std::string type, std::string name);
	~Zombie();

	void announce();

	std::string	type;
	std::string	name;
};

#endif /* ZOMBIE_HPP */
