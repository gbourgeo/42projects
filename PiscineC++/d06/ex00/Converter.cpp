// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/08 18:01:06 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/08 22:31:26 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Converter.hpp"

Converter::Converter(): _nb(""), _conv("")
{}

Converter::Converter(Converter const & src)
{
	*this = src;
}

Converter & Converter::operator=(Converter const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

Converter::~Converter()
{}

void Converter::doConversions(std::string const & nb)
{
	this->_nb = nb;
	doCharConversion();
	doIntConversion();
	doFloatConversion();
	doDoubleConversion();
}

void Converter::doCharConversion()
{
	this->_conv = "char: ";
	if (this->_nb[0] != '-' && (this->_nb[0] < '0' || this->_nb[0] > '9')) {
		this->_conv += "impossible";
	} else {
		try {
			char c = static_cast<char>(std::stoi(this->_nb));
		
			if (c < 32 || c >= 127)
				this->_conv += "Non displayable";
			else {
				this->_conv += "'";
				this->_conv += c;
				this->_conv += "'";
			}
		} catch (std::invalid_argument &e) {
			this->_conv += "invalid argument";
		} catch (std::out_of_range &e) {
			this->_conv += "out of range";
		}
	}
	std::cout << this->_conv << std::endl;
}

void Converter::doIntConversion()
{
	this->_conv = "int: ";
	if (this->_nb[0] != '-' && (this->_nb[0] < '0' || this->_nb[0] > '9')) {
		this->_conv += "impossible";
	} else {
		try {
			int i = std::stoi(this->_nb);
			this->_conv += std::to_string(i);
		} catch (std::invalid_argument &e) {
			this->_conv += "invalid argument";
		} catch (std::out_of_range &e) {
			this->_conv += "out of range";
		}
	}
	std::cout << this->_conv << std::endl;
}

void Converter::doFloatConversion()
{
	this->_conv = "float: ";
	if (this->_nb == "-inff" || this->_nb == "-inf")
		this->_conv += "-inff";
	else if (this->_nb == "+inff" || this->_nb == "inff" || this->_nb == "+inf" || this->_nb == "inf")
		this->_conv += "inff";
	else if (this->_nb == "nanf" || this->_nb == "nan")
		this->_conv += "nanf";
	if (this->_nb[0] != '-' && (this->_nb[0] < '0' || this->_nb[0] > '9')) {
		this->_conv += "invalid argument";
	} else {
		try {
			float f = std::stof(this->_nb);

			this->_conv += std::to_string(f);
			for (int i = this->_conv.length();  i > 0 && this->_conv[i - 1] == '0'; i--) {
				if (i > 1 && this->_conv[i - 2] != '.')
					this->_conv.erase(i - 1);
			}
			this->_conv += "f";
		} catch (std::invalid_argument &e) {
			this->_conv += "invalid argument";
		} catch (std::out_of_range &e) {
			this->_conv += "out of range";
		}
	}
	std::cout << this->_conv << std::endl;
}

void Converter::doDoubleConversion()
{
	this->_conv = "double: ";
	if (this->_nb == "-inff" || this->_nb == "-inf")
		this->_conv += "-inf";
	else if (this->_nb == "+inff" || this->_nb == "inff" || this->_nb == "+inf" || this->_nb == "inf")
		this->_conv += "inf";
	else if (this->_nb == "nanf" || this->_nb == "nan")
		this->_conv += "nan";
	if (this->_nb[0] != '-' && (this->_nb[0] < '0' || this->_nb[0] > '9')) {
		this->_conv += "impossible";
	} else {
		try {
			double f = std::stod(this->_nb);

			this->_conv += std::to_string(f);
			for (int i = this->_conv.length();  i > 0 && this->_conv[i - 1] == '0'; i--) {
				if (i > 1 && this->_conv[i - 2] != '.')
					this->_conv.erase(i - 1);
			}
		} catch (std::invalid_argument &e) {
			this->_conv += "invalid argument";
		} catch (std::out_of_range &e) {
			this->_conv += "out of range";
		}
	}
	std::cout << this->_conv << std::endl;
}
