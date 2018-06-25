#include<iostream>
#include<fstream>
#include<cstdlib>
int create(int i) {
	std::string file = "Sully_" + std::to_string(i) + ".cpp";
	std::ifstream in(file);
	if (in.good())
		return 1;
	std::ofstream out(file, std::ofstream::out | std::ofstream::trunc);
	if (!out.is_open())
		return -1;
	std::string c = R"(#include<iostream>
#include<fstream>
#include<cstdlib>
int create(int i) {
	std::string file = "Sully_" + std::to_string(i) + ".cpp";
	std::ifstream in(file);
	if (in.good())
		return 1;
	std::ofstream out(file, std::ofstream::out | std::ofstream::trunc);
	if (!out.is_open())
		return -1;
)";
	std::string e = R"(
	out << c
		<< "	std::string c = R\"(" << c << ")\";\n"
		<< "	std::string e = R\"(" << e << ")\";\n"
		<< "	std::string d = R\"(" << d << ")\";\n"
		<< e << i
		<< d;
	return 0;
}
int main(){
	int i = )";
	std::string d = R"(;
	if (i <= 0)
		return 0;
	if (!create(i - 1)) {
		std::string cmd = "g++ -Wall -Werror -Wextra -std=c++11 -o Sully_" + std::to_string(i - 1) +
			" Sully_" + std::to_string(i - 1) + ".cpp && ./Sully_" + std::to_string(i - 1);
		std::system(cmd.c_str());
	}
	return 0;
}
)";

	out << c
		<< "	std::string c = R\"(" << c << ")\";\n"
		<< "	std::string e = R\"(" << e << ")\";\n"
		<< "	std::string d = R\"(" << d << ")\";\n"
		<< e << i
		<< d;
	return 0;
}
int main(){
	int i = 5;
	if (i <= 0)
		return 0;
	if (!create(i - 1)) {
		std::string cmd = "g++ -Wall -Werror -Wextra -std=c++11 -o Sully_" + std::to_string(i - 1) +
			" Sully_" + std::to_string(i - 1) + ".cpp && ./Sully_" + std::to_string(i - 1);
		std::system(cmd.c_str());
	}
	return 0;
}
