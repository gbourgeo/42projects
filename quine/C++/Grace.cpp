/*
  This program will print its code source in a file only using macros.
*/
#include <iostream>
#include <fstream>
#define OPEN std::ofstream f("Grace_kid.cpp",std::ofstream::out|std::ofstream::trunc);
#define WRITE f << c << " std::string c=R\"(" << c << ")\";" << " std::string d=R\"(" << d << ")\";" << d;
#define MAIN int main(){ OPEN if (!f.is_open()) return -1; std::string c=R"(/*
  This program will print its code source in a file only using macros.
*/
#include <iostream>
#include <fstream>
#define OPEN std::ofstream f("Grace_kid.cpp",std::ofstream::out|std::ofstream::trunc);
#define WRITE f << c << " std::string c=R\"(" << c << ")\";" << " std::string d=R\"(" << d << ")\";" << d;
#define MAIN int main(){ OPEN if (!f.is_open()) return -1;)"; std::string d=R"( WRITE }
MAIN
)"; WRITE }
MAIN
