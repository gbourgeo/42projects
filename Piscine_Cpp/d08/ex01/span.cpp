// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   span.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/10 13:42:55 by root              #+#    #+#             //
//   Updated: 2018/07/10 15:01:01 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <climits>
#include <algorithm>
#include "span.hpp"

Span::Span(): _nbElems(0)
{}

Span::Span(unsigned int N): _nbElems(N)
{}

Span::Span(Span const & src)
{
	*this = src;
}

Span::~Span()
{}

Span & Span::operator=(Span const & rhs)
{
	if (this != &rhs)
	{
		this->_elems = rhs.getElems();
		this->_nbElems = rhs.getNbElems();
	}
	return *this;
}

std::list<int> Span::getElems() const
{
	return this->_elems;
}

unsigned int Span::getNbElems() const
{
	return this->_nbElems;
}

void Span::addNumber(int nb)
{
	if (this->_elems.size() == this->_nbElems)
		throw std::exception();
	this->_elems.push_back(nb);
}

int Span::shortestSpan() const
{
	int								span = INT_MAX;
	std::list<int>::const_iterator	it;
	std::list<int>::const_iterator	it2;

	if (this->_elems.size() < 2)
		throw std::exception();
	for (it = this->_elems.begin(); it != this->_elems.end(); it++) {
		it2 = it;
		it2++;
		while (it2 != this->_elems.end()) {
			if (std::abs(*it - *it2) < span)
				span = std::abs(*it - *it2);
			it2++;
		}
	}
	return span;
}

int Span::longestSpan() const
{
	if (this->_elems.size() < 2)
		throw std::exception();
	return std::abs(*std::min_element(this->_elems.begin(), this->_elems.end()) - *std::max_element(this->_elems.begin(), this->_elems.end()));
}
