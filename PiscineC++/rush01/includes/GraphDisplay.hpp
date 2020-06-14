#ifndef GRAPHDISPLAY_HPP
# define GRAPHDISPLAY_HPP

# include "AMonitorDisplay.hpp"

class GraphDisplay: public AMonitorDisplay
{
public:
	GraphDisplay();
	~GraphDisplay();
	GraphDisplay(GraphDisplay const & src);
	GraphDisplay & operator=(GraphDisplay const & rhs);

	int				init();
	void			quit();
	void			*getWindow() const;
	void			affModule();

private:
};

#endif
