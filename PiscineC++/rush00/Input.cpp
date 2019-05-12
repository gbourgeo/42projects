#include "Input.hpp"

/**
 * Constructor / Destructor
 */

Input::Input(void): Logger("default.log") {}

Input::Input(std::string logFileName): Logger(logFileName) {}

Input::Input(Input const &ref): Logger(ref.getFilename()) {
    if (this != &ref) {
        this->setLastKey(ref.getLastKey());
    }
}

Input::~Input(void) {}

/**
 * Getters
 */

int         Input::getLastKey(void) const {
    return this->lastKey;
}

/**
 * Setters
 */

void        Input::setLastKey(int c) {
    this->lastKey = c;
    this->log(FILE, this->makeKeyLog(c));
}



