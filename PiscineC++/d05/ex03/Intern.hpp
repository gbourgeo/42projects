// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Intern.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 19:45:51 by root              #+#    #+#             //
//   Updated: 2018/07/06 19:57:23 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INTERN_HPP
# define INTERN_HPP

#include "Form.hpp"

class Intern
{
public:
	Intern();
	Intern(Intern const & src);
	Intern & operator=(Intern const & rhs);
	~Intern();

	Form *		makeForm(std::string const &, std::string const &);
};

#endif
