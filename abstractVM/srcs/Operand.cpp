/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 01:41:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/06 01:50:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

Operand::Operand(): _value(0), _type(0), _precision(0)
{}

Operand::~Operand()
{}

Operand::Operand(Operand const & src)
{
	*this = src;
}

Operand & Operand::operator=(Operand const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

int Operand::getPrecision( void ) const
{}

eOperandType Operand::getType( void ) const
{}

IOperand const * Operand::operator+( IOperand const & rhs ) const
{}

IOperand const * Operand::operator-( IOperand const & rhs ) const
{}

IOperand const * Operand::operator*( IOperand const & rhs ) const
{}

IOperand const * Operand::operator/( IOperand const & rhs ) const
{}

IOperand const * Operand::operator%( IOperand const & rhs ) const
{}

std::string const & Operand::toString( void ) const
{}
