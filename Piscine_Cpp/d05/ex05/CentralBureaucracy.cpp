// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CentralBureaucracy.cpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/08 03:40:50 by root              #+#    #+#             //
//   Updated: 2018/07/08 06:10:26 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <ctime>
#include "CentralBureaucracy.hpp"

CentralBureaucracy::CentralBureaucracy(): _queue(0)
{
	for (int i = 0; i < OFFICEBLOCKS; i++) {
		this->_blocks[i] = 0;
	}
	std::srand(std::time(NULL));
}

CentralBureaucracy::CentralBureaucracy(CentralBureaucracy const & src)
{
	*this = src;
}

CentralBureaucracy & CentralBureaucracy::operator=(CentralBureaucracy const & rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < OFFICEBLOCKS; i++) {
			this->_blocks[i] = rhs.getBlocks(i);
		}
	}
	return *this;
}

CentralBureaucracy::~CentralBureaucracy()
{
	for ( int i = 0; i < OFFICEBLOCKS; i++) {
		if (this->_blocks[i]) {
			delete this->_blocks[i]->getIntern();
			delete this->_blocks[i];
		}
	}
}

void CentralBureaucracy::addBureaucrat(Bureaucrat *x)
{
	for (int i = 0; i < OFFICEBLOCKS; i++) {
		if (this->_blocks[i] == 0) {
			this->_blocks[i] = new OfficeBlock();
			this->_blocks[i]->setIntern(new Intern);
			this->_blocks[i]->setSigningBureaucrat(x);
			return ;
		}
		if (this->_blocks[i]->getExecutingBureaucrat() == 0) {
			this->_blocks[i]->setExecutingBureaucrat(x);
			return ;
		}
	}
	// CentralBureaucracy don't store Bureaucrats;
}

void CentralBureaucracy::queueUp(std::string const & person)
{
	t_queue		*ptr;

	if (this->_queue == 0) {
		this->_queue = new t_queue;
		this->_queue->name = person;
		this->_queue->next = 0;
		return ;
	}
	ptr = this->_queue;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new t_queue;
	ptr->next->name = person;
	ptr->next->next = 0;
}

void CentralBureaucracy::doBureaucracy() const
{
	static std::string 	forms[] = { "shrubbery creation", "robotomy request", "presidential pardon" };

	if (this->_queue == 0)
		return ;
	for (t_queue *ptr = this->_queue; ptr; ptr = ptr->next) {
		for (int i = 0; i < OFFICEBLOCKS; i++) {
			if (this->_blocks[i]) {
				try {
					this->_blocks[i]->doBureaucracy(forms[std::rand() % 3], ptr->name);
				} catch (std::exception &e) {
					std::cout << e.what() << std::endl;
				}
			}
		}
	}
}

OfficeBlock *CentralBureaucracy::getBlocks(int idx) const
{
	if (idx < 0 || idx >= OFFICEBLOCKS)
		return 0;
	return this->_blocks[idx];
}
