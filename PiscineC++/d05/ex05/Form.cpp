// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Form.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 13:58:43 by root              #+#    #+#             //
//   Updated: 2018/07/06 17:57:23 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Form.hpp"

Form::Form(): _name(""), _signed(false), _signGrade(150), _execGrade(150)
{}

Form::Form(std::string const & name, int const sign, int const exec):
	_name(name), _signed(false), _signGrade(sign), _execGrade(exec)
{
	if (this->_signGrade < 1 || this->_execGrade < 1)
		throw Form::GradeTooHighException();
	if (this->_signGrade > 150 || this->_execGrade > 150)
		throw Form::GradeTooLowException();
}

Form::Form(Form const & src)
{
	*this = src;
}

Form & Form::operator=(Form const & rhs)
{
	if (this != &rhs)
	{
		this->_name = rhs.getName();
		this->_signed = rhs.getSigned();
		this->_signGrade = rhs.getSignGrade();
		this->_execGrade = rhs.getExecGrade();
		if (this->_signGrade < 1 || this->_execGrade < 1)
			throw Form::GradeTooHighException();
		if (this->_signGrade > 150 || this->_execGrade > 150)
			throw Form::GradeTooLowException();
	}
	return *this;
}

Form::~Form()
{}

std::string const Form::getName() const
{
	return this->_name;
}

bool Form::getSigned() const
{
	return this->_signed;
}

int Form::getSignGrade() const
{
	return (int)this->_signGrade;
}

int Form::getExecGrade() const
{
	return (int)this->_execGrade;
}

void Form::beSigned(Bureaucrat & bureaucrat)
{
	if (bureaucrat.getGrade() > this->_signGrade)
		throw Form::GradeTooLowException();
	this->_signed = true;
}

void Form::execute(Bureaucrat const & executor) const
{
	if (!this->_signed)
		throw Form::FormNotSignedException();
	else if (executor.getGrade() > this->_execGrade)
		throw Form::GradeTooLowException();
}

std::ostream & operator<<(std::ostream & os, Form const & src)
{
	os << src.getName() << " is ";
	if (src.getSigned())
		os << "signed";
	else
		os << "not signed";
	os << ". Mininmum grade for signature: " << src.getSignGrade();
	os << ". Minimum grade for execute: " << src.getExecGrade();
	os << std::endl;
	return os;
}
