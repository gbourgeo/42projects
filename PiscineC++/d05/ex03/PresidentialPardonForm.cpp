// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PresidentialPardonForm.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 16:28:50 by root              #+#    #+#             //
//   Updated: 2018/07/06 20:26:51 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm():
	Form("Presidential Pardon Form", PRESIDENTIAL_FORM_SIGN, PRESIDENTIAL_FORM_EXEC),  _target("")
{}

PresidentialPardonForm::PresidentialPardonForm(std::string const & target):
	Form("Presidential Pardon Form", PRESIDENTIAL_FORM_SIGN, PRESIDENTIAL_FORM_EXEC), _target(target)
{}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & src):
	Form("Presidential Pardon Form", PRESIDENTIAL_FORM_SIGN, PRESIDENTIAL_FORM_EXEC)
{
	*this = src;
}

PresidentialPardonForm & PresidentialPardonForm::operator=(PresidentialPardonForm const & rhs)
{
	if (this != &rhs)
	{
		this->_target = rhs.getTarget();
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{}

std::string PresidentialPardonForm::getTarget() const
{
	return this->_target;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
	Form::execute(executor);
	std::cout << this->_target << " has been pardoned by Zafod Beeblebrox." << std::endl;
}
