// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OfficeBlock.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 21:08:27 by root              #+#    #+#             //
//   Updated: 2018/07/08 06:11:26 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "OfficeBlock.hpp"

OfficeBlock::OfficeBlock(): _intern(0), _sBureaucrat(0), _xBureaucrat(0)
{}

OfficeBlock::OfficeBlock(Intern *i, Bureaucrat *s, Bureaucrat *x):
	_intern(i), _sBureaucrat(s), _xBureaucrat(x)
{}

OfficeBlock::~OfficeBlock()
{}

void OfficeBlock::setIntern(Intern *i)
{
	this->_intern = i;
}

void OfficeBlock::setSigningBureaucrat(Bureaucrat *s)
{
	this->_sBureaucrat = s;
}

void OfficeBlock::setExecutingBureaucrat(Bureaucrat *x)
{
	this->_xBureaucrat = x;
}

Intern * OfficeBlock::getIntern() const
{
	return this->_intern;
}

Bureaucrat * OfficeBlock::getSigningBureaucrat() const
{
	return this->_sBureaucrat;
}

Bureaucrat * OfficeBlock::getExecutingBureaucrat() const
{
	return this->_xBureaucrat;
}

void OfficeBlock::doBureaucracy(std::string const & formname, std::string const & target)
{
	Form		*form = 0;

	if (!this->_intern)
		throw OfficeBlock::NoInternAssignedException();
	if (!this->_sBureaucrat)
		throw OfficeBlock::NoSigningBureaucratException();
	if (!this->_xBureaucrat)
		throw OfficeBlock::NoExecutingBureaucratException();
	if (!(form = this->_intern->makeForm(formname, target)))
		throw OfficeBlock::NoFormCreatedException();
	if (!this->_sBureaucrat->signForm(*form)) {
		delete form;
		throw OfficeBlock::NoFormSignedException();
	}
	if (!(this->_xBureaucrat->executeForm(*form))) {
		delete form;
		throw OfficeBlock::NoFormExecutedException();
	}
	delete form;
}
