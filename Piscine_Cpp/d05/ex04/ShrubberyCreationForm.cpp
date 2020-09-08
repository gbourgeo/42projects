// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 16:28:50 by root              #+#    #+#             //
//   Updated: 2018/07/06 21:48:26 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm():
	Form("Shruberry Creation Form", SHRUBBERY_FORM_SIGN, SHRUBBERY_FORM_EXEC),  _target("")
{}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const & target):
	Form("Shruberry Creation Form", SHRUBBERY_FORM_SIGN, SHRUBBERY_FORM_EXEC), _target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & src):
	Form("Shruberry Creation Form", SHRUBBERY_FORM_SIGN, SHRUBBERY_FORM_EXEC)
{
	*this = src;
}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & rhs)
{
	if (this != &rhs)
	{
		this->_target = rhs.getTarget();
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{}

std::string ShrubberyCreationForm::getTarget() const
{
	return this->_target;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	Form::execute(executor);
	std::cout << executor.getName() << " executes " << Form::getName() << std::endl;
	std::string filename = this->_target + "_shrubbery";
	std::ofstream file(filename.c_str(), std::ios::app);
	if (file.is_open()) {
		file << "" << std::endl;
		file << "    oxoxoo    ooxoo" << std::endl;
		file << "  ooxoxo oo  oxoxooo" << std::endl;
		file << " oooo xxoxoo ooo ooox" << std::endl;
		file << " oxo o oxoxo  xoxxoxo" << std::endl;
		file << "  oxo xooxoooo o ooo" << std::endl;
		file << "    ooo\\oo\\  /o/o" << std::endl;
		file << "        \\  \\/ /" << std::endl;
		file << "         |   /" << std::endl;
		file << "         |  |" << std::endl;
		file << "         | D|" << std::endl;
		file << "         |  |" << std::endl;
		file << "         |  |" << std::endl;
		file << "  ______/____\\____" << std::endl;
		file << "" << std::endl;
		file.close();
	}
}
