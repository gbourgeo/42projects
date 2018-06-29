// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Human.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 19:09:46 by root              #+#    #+#             //
//   Updated: 2018/06/29 19:48:00 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HUMAN_HPP
# define HUMAN_HPP

# define callMemberFunction(object, ptr) ((object).*(ptr))

#include <string>

class Human
{
private:
	void	meleeAttack(std::string const & target);
	void	rangedAttack(std::string const & target);
	void	intimidatingShout(std::string const & target);

public:
	void	action(std::string const & action_name, std::string const & target);
};

typedef void (Human::*HumanActions)(std::string const &);


#endif
