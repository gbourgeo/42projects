#include <iostream>
#include <fstream>
int main(){
	std::ofstream f("Grace_kid.cpp",std::ofstream::out|std::ofstream::trunc);
	if (!f.is_open()) return -1;
	std::string c=R"(#include <iostream>
#include <fstream>
int main(){
	std::ofstream f("Grace_kid.cpp",std::ofstream::out|std::ofstream::trunc);
	if (!f.is_open()) return -1;
)";
	std::string d=R"(
	f << c
	  << "	std::string c=R\"(" << c << ")\";\n"
	  << "	std::string d=R\"(" << d << ")\";\n"
	  << d;
}
)";

	f << c
	  << "	std::string c=R\"(" << c << ")\";\n"
	  << "	std::string d=R\"(" << d << ")\";\n"
	  << d;
}
