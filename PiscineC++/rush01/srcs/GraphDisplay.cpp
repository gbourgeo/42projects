#include "GraphDisplay.hpp"

GraphDisplay::GraphDisplay()
{}

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

int GraphDisplay::init()
{
	/* load graphical display */
	return (0);
}

void GraphDisplay::quit()
{
	/* unload graphical display */
}

void *GraphDisplay::getWindow() const
{
	return nullptr;
}

int GraphDisplay::affModules() const
{
	return (1);
}