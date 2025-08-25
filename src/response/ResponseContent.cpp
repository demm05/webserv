#include "ResponseContent.hpp"
#include <fstream>
#include <sstream>

static std::string toLower(const std::string &s) {
    std::string r = s;
    for (std::string::size_type i = 0; i < r.size(); ++i)
        r[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(r[i])));
    return r;
}

http::ResponseContent::ResponseContent() : body_(""), type_("") {
}

http::ResponseContent::ResponseContent(const char *path) {
    std::ifstream file(path);
    std::string fileText;
    if (file) {
        while (std::getline(file, fileText)) {
            body_ += fileText;
        }
        setFileType(path);
    }
}

http::ResponseContent::ResponseContent(const std::string &body, const std::string &type)
    : body_(body), type_(type) {
}

http::ResponseContent::ResponseContent(const http::ResponseContent &other)
    : body_(other.body_), type_(other.type_) {
}

http::ResponseContent &http::ResponseContent::operator=(const http::ResponseContent &other) {
    if (this != &other) {
        body_ = other.body_;
        type_ = other.type_;
    }
    return *this;
}

const std::string &http::ResponseContent::getBody() const {
    return body_;
}

const std::string &http::ResponseContent::getType() const {
    return type_;
}

size_t http::ResponseContent::getContentLength() const {
    return body_.size();
}

http::ResponseContent::~ResponseContent() {
}

void http::ResponseContent::setFileType(const std::string &path) {
    size_t pos = path.find_last_of('.');
    if (pos != std::string::npos) {
        std::string extension = toLower(path.substr(pos + 1));
        std::ifstream file(MIME_TYPES_PATH);
        std::string fileText;
        // Read the MIME types file line by line
        // and check if the extension matches any of the defined types
        if (file) {
            while (std::getline(file, fileText)) {
                std::string mimeType = fileText.substr(0, fileText.find_first_of(' '));
                std::string extensions = fileText.substr(fileText.find_first_of(' ') + 1);
                std::istringstream iss(extensions);
                std::string ext;
                while (iss >> ext) {
                    if (extension == ext) {
                        type_ = mimeType;
                        return;
                    }
                }
            }
        }
    }
    type_ = "text/plain"; // Default MIME type if no match is found
}
