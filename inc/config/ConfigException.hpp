#pragma once

#include <exception>
#include <string>
#include <iostream>

namespace config {

class ConfigException : public std::exception {
private:
    std::string message_;

public:
    ConfigException(std::string const &message) : message_(message) {
    }
    virtual ~ConfigException() throw() {
    }
    char const *what(void) const throw() {
        return message_.c_str();
    }
};

class ConfigError : public ConfigException {
public:
    ConfigError(std::string const &message) : ConfigException("Error: " + message) {
    }
};

class ConfigWarning : public ConfigException {
public:
    ConfigWarning(std::string const &message) : ConfigException("Warning: " + message) {
    }
};

// TODO: use global variable instead of macro
void issue_warning(std::string const &msg) {
#ifdef WERROR
    throw ConfigWarning(msg);
#else
    std::cerr << "Warning: " << msg << std::endl;
#endif
}

} // namespace config
