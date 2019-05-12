#ifndef LOGGER_HPP
 #define LOGGER_HPP

#define CONSOLE "console"
#define FILE "file"

class Logger {

public:
	Logger(std::string filename);
	~Logger(void);

	void 			log(std::string const & dest, std::string const & message);
	void 			log(std::string const & dest, std::string const & message, int value);

	std::string		getFilename(void) const;
	void			setFilename(std::string name);

protected:

	// Method
	std::string		formatLogDate(void);
	std::string 	makeLogEntry(std::string);
	std::string		makeKeyLog(int keyValue);

private:

	void 			logToConsole(std::string);
	void 			logToFile(std::string);

	// Property
	std::string		filename;
};

#endif