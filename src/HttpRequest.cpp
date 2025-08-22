#include "HttpRequest.hpp"
#include <sstream>
#include <iostream>

HttpRequest::HttpRequest() : isValid_(false) {
}

HttpRequest::~HttpRequest() {
}

// TODO write documentation for this
// a bit tricky part
// Find end of headers
// size_t headerEnd = data.find("\r\n\r\n");
// if (headerEnd == std::string::npos) {
//     headerEnd = data.find("\n\n");  // Try LF only
//     if (headerEnd == std::string::npos) {
//         return false;
//     }
// }
bool HttpRequest::parseRequest(const char *rawData, int length) {
    clear();

    std::string data(rawData, length);

    size_t headerEnd = data.find("\r\n\r\n");
    if (headerEnd == std::string::npos) {
        headerEnd = data.find("\n\n");
        if (headerEnd == std::string::npos) {
            return false;
        }
    }
    std::string headerSection = data.substr(0, headerEnd);
    std::istringstream headerStream(headerSection);
    std::string line;

    if (!std::getline(headerStream, line)) {
        return false;
    }
    if (!parseRequestLine(line)) {
        return false;
    }
    if (!parseHeaders(headerSection)) {
        return false;
    }

    isValid_ = true;
    return true;
}

bool HttpRequest::parseRequestLine(const std::string &line) {
    std::istringstream iss(line);

    if (!(iss >> method_ >> path_ >> version_)) {
        return false;
    }
    if (!version_.empty() && version_[version_.length() - 1] == '\r') {
        version_ = version_.substr(0, version_.length() - 1);
    }

    std::cout << "Parsed HTTP: " << method_ << " " << path_ << " " << version_ << std::endl;
    return true;
}

bool HttpRequest::parseHeaders(const std::string &headerSection) {
    std::istringstream headerStream(headerSection);
    std::string line;

    std::getline(headerStream, line);
    while (std::getline(headerStream, line) && !line.empty()) {
        if (!line.empty() && line[line.length() - 1] == '\r') {
            line = line.substr(0, line.length() - 1);
        }

        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string name = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            while (!value.empty() && value[0] == ' ') {
                value = value.substr(1);
            }
            headers_[name] = value;
        }
    }
    return true;
}

const std::string &HttpRequest::getMethod() const {
    return method_;
}
const std::string &HttpRequest::getPath() const {
    return path_;
}
const std::string &HttpRequest::getVersion() const {
    return version_;
}

const std::string &HttpRequest::getHeader(const std::string &name) const {
    static std::string empty;
    std::map<std::string, std::string>::const_iterator it = headers_.find(name);
    return (it != headers_.end()) ? it->second : empty;
}

bool HttpRequest::isValid() const {
    return isValid_;
}

void HttpRequest::clear() {
    method_.clear();
    path_.clear();
    version_.clear();
    headers_.clear();
    isValid_ = false;
}