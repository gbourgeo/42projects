#include <iostream>
int main(){
	std::string c=R"(#include <iostream>
int main(){
)";
	std::string d=R"(
	std::cout << c
			  << "	std::string c=R\"(" << c << ")\";\n"
			  << "	std::string d=R\"(" << d << ")\";\n"
			  << d;
}
)";

	std::cout << c
			  << "	std::string c=R\"(" << c << ")\";\n"
			  << "	std::string d=R\"(" << d << ")\";\n"
			  << d;
}
