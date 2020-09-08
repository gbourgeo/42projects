#ifndef INPUT_HPP
 #define INPUT_HPP

class Input
{
public:
	/*
	* Constructor / Destructor
	*/
	Input(void);
	Input(Input const &ref);
	~Input(void);

	/*
	* Overload
	*/
	Input & operator=(Input const &ref);

	/*
	* Getters
	*/
	int		getLastKey(void) const;

	/*
	* Setters
	*/
	void	setLastKey(int c);

private:
	/*
	* Attributes
	*/
	int		lastKey;
};

#endif