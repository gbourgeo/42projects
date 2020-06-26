#ifndef GRAPHDISPLAY_HPP
# define GRAPHDISPLAY_HPP

# include "AMonitorDisplay.hpp"

class GraphDisplay: public AMonitorDisplay
{
public:
	GraphDisplay(std::string const & modulePath);
	~GraphDisplay();
	GraphDisplay(GraphDisplay const & src);
	GraphDisplay & operator=(GraphDisplay const & rhs);

	void			start() const;

private:
	GraphDisplay();
};

#endif
