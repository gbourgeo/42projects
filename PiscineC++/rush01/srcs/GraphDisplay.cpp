#include "GraphDisplay.hpp"

GraphDisplay::GraphDisplay()
{}

GraphDisplay::GraphDisplay(std::string const & modulePath)
{
	this->_moduleHandler = new ModuleHandler(modulePath);
	if (this->_moduleHandler == nullptr)
		return ;
}

GraphDisplay::~GraphDisplay()
{}

GraphDisplay::GraphDisplay(GraphDisplay const & src)
{
	*this = src;
}

GraphDisplay & GraphDisplay::operator=(GraphDisplay const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

void GraphDisplay::start() const
{
}