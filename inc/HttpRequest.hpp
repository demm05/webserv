#pragma once
#include <string>
#include <map>

// TODO Documentation for the http request protocol
//     std::string method_;     // GET, POST, etc.
//    std::string path_;       // /index.html
//     std::string version_;    // HTTP/1.1

class HttpRequest {
public:
    HttpRequest();
    ~HttpRequest();

    bool parseRequest(const char *rawData, int length);

    // Getters
    const std::string &getMethod() const;
    const std::string &getPath() const;
    const std::string &getVersion() const;
    const std::string &getHeader(const std::string &name) const;
    bool isValid() const;
    void clear();

private:
    std::string method_;  // GET, POST, etc.
    std::string path_;    // /index.html
    std::string version_; // HTTP/1.1
    std::map<std::string, std::string> headers_;
    bool isValid_;

    bool parseRequestLine(const std::string &line);
    bool parseHeaders(const std::string &headerSection);
};