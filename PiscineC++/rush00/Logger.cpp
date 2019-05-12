#include "main.hpp"

typedef void (Logger::*t_loggerFunctions)(std::string logEntry);

Logger::Logger(std::string filename): filename(filename) {}

Logger::~Logger(void) {}

std::string		Logger::getFilename(void) const {
	return this->filename;
}

void			Logger::setFilename(std::string filename) {
	this->filename = filename;
}

std::string 		Logger::formatLogDate(void) {
    time_t 			rawtime;
  	struct tm 		*timeinfo;

  	char *buffer = new char [20];

  	time (&rawtime);
  	timeinfo = localtime (&rawtime);

  	strftime (buffer,80,"[%Y_%m_%d_%H%M]",timeinfo);

  	return std::string(buffer);
}

std::string			Logger::makeLogEntry(std::string entry) {
    if (!entry.empty()) {
		return this->formatLogDate().append(entry) + "\n";
	} else {
		return NULL;
	}
}

std::string			Logger::makeKeyLog(int keyValue) {
	std::stringstream 	ss;
	std::string			*ptr;

	ss << " New Key Value -> ";
	switch (keyValue) {
		case (KEY_UP) : {	
			ptr = new std::string("Key Up");
			break;
		}
		case (KEY_DOWN) : {
			ptr = new std::string("Key Down");
			break;
		}
		case (KEY_LEFT) : {
			ptr = new std::string("Key Left");
			break;
		}
		case (KEY_RIGHT) : {
			ptr = new std::string("Key Right");
			break;
		}
		case 27 : {
			ptr = new std::string("Escape");
			break;
		}
		default: ptr = new std::string(std::to_string(keyValue));
	};

	ss << *ptr;
	delete ptr;
	return ss.str();
}

void				Logger::log(std::string const & dest, std::string const & message) {

	if (!dest.empty() && !message.empty()) {
		t_loggerFunctions	logFuncs[2] = {&Logger::logToConsole, &Logger::logToFile};
		std::string			funcName[2] = {CONSOLE, FILE};

		for (int i = 0; i < 2; i++) {
			if (dest == funcName[i]) {
				(*this.*logFuncs[i])(message);
			}
		}
	};
}

void				Logger::log(std::string const & dest, std::string const & message, int value) {

	std::stringstream	ss;

	ss << message;
	ss << std::to_string(value);

	if (!dest.empty() && !message.empty()) {
		t_loggerFunctions	logFuncs[2] = {&Logger::logToConsole, &Logger::logToFile};
		std::string			funcName[2] = {CONSOLE, FILE};

		for (int i = 0; i < 2; i++) {
			if (dest == funcName[i]) {
				(*this.*logFuncs[i])(ss.str());
			}
		}
	};
}

void				Logger::logToConsole(std::string logEntry) {
	std::cout << this->makeLogEntry(logEntry);
}

void 				Logger::logToFile(std::string logEntry) {

	std::ofstream 	myfile;

	myfile.open (this->filename, std::ios::app | std::ios::out);
	if (myfile.is_open()) {
	  	myfile << this->makeLogEntry(logEntry);
	  	myfile.close();
  	} else {
  		std::cout << "Something went wrong at the opening" << std::endl;
  	}
}