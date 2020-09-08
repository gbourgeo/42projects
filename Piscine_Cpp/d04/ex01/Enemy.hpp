// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Enemy.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/04 11:48:54 by root              #+#    #+#             //
//   Updated: 2018/07/04 12:33:22 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ENEMY_HPP
# define ENEMY_HPP

#include <string>

class Enemy
{
public:
	Enemy(int hp, std::string const & type);
	Enemy(Enemy const & src);
	Enemy & operator=(Enemy const & rhs);
	virtual ~Enemy();

	std::string		getType() const;
	int				getHP() const;

	virtual void	takeDamage(int);
	
protected:
	Enemy();

	int				_hp;
	std::string		_type;
};

#endif
