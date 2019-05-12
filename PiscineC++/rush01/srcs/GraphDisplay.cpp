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

void GraphDisplay::init()
{
	/* load graphical display */
}
