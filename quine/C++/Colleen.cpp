#include <iostream>
/*
	This program prints its own code source.
*/
static void print(std::string &c, std::string &d)
{
	std::cout << c << "	std::string c=R\"(" << c << ")\";\n"
	<< "	std::string d=R\"(" << d << ")\";\n" << d;
}

int main(){
	/*
	  This is what we call a quine.
	*/
	std::string c=R"(#include <iostream>
/*
	This program prints its own code source.
*/
static void print(std::string &c, std::string &d)
{
	std::cout << c << "	std::string c=R\"(" << c << ")\";\n"
	<< "	std::string d=R\"(" << d << ")\";\n" << d;
}

int main(){
	/*
	  This is what we call a quine.
	*/
)";
	std::string d=R"(	print(c, d);
}
)";
	print(c, d);
}
