#include "AMonitorModule.hpp"

AMonitorModule::AMonitorModule(AMonitorModule const & src)
{
	*this = src;
}

AMonitorModule & AMonitorModule::operator=(AMonitorModule const & rhs)
{
	if (this != &rhs)
	{
		this->_title = rhs._title;
		this->_minWidth = rhs._minWidth;
		this->_minHeigth = rhs._minHeigth;
	}
	return *this;
}
