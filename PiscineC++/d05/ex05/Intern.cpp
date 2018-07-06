// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Intern.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 19:49:11 by root              #+#    #+#             //
//   Updated: 2018/07/06 20:24:19 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

Intern::Intern()
{}

Intern::Intern(Intern const & src)
{
	*this = src;
}

Intern & Intern::operator=(Intern const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

Intern::~Intern()
{}

Form * Intern::makeForm(std::string const & formName, std::string const & target)
{
	static std::string 	forms[] = { "shrubbery creation", "robotomy request", "presidential pardon" };
	Form				*form;

	for (size_t i = 0; i < sizeof(forms) / sizeof(*forms); i++) {
		if (forms[i] == formName) {
			if (i == 0) {
				form = new ShrubberyCreationForm(target);
			} else if (i == 1) {
				form = new RobotomyRequestForm(target);
			} else {
				form = new PresidentialPardonForm(target);
			}
			std::cout << "Intern creates " << form->getName() << std::endl;
			return form;
		}
	}
	return 0;
}
