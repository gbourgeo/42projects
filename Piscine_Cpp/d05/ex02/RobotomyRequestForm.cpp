// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RobotomyRequestForm.cpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 16:28:50 by root              #+#    #+#             //
//   Updated: 2018/07/06 20:27:26 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm():
	Form("Robotomy Request Form", ROBOTOMY_FORM_SIGN, ROBOTOMY_FORM_EXEC),  _target("")
{}

RobotomyRequestForm::RobotomyRequestForm(std::string const & target):
	Form("Robotomy Request Form", ROBOTOMY_FORM_SIGN, ROBOTOMY_FORM_EXEC), _target(target)
{}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & src):
	Form("Robotomy Request Form", ROBOTOMY_FORM_SIGN, ROBOTOMY_FORM_EXEC)
{
	*this = src;
}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & rhs)
{
	if (this != &rhs)
	{
		this->_target = rhs.getTarget();
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{}

std::string RobotomyRequestForm::getTarget() const
{
	return this->_target;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	static bool	robotomized = true;

	Form::execute(executor);
	std::cout << "** DRIIIIIIIIIIIIIIIIIIIIIIIIIIILL **" << std::endl;
	if (robotomized)
		std::cout << this->_target << " has been robotomized !" << std::endl;
	else
		std::cout << this->_target << " failed to be robotomized !" << std::endl;
	robotomized = !robotomized;
}
