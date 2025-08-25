#pragma once

#include <string>
#include <map>

namespace http {

enum HttpMethod { GET, POST, PUT, DELETE, UNKNOWN };

/**
 * @class HttpRequest
 * @brief A data container for a parsed HTTP request.
 *
 * This object holds all the structured information from a client's raw
 * HTTP request message.
 */
class HttpRequest {
public:
    typedef std::map<std::string, std::string> HeaderMap;

    HttpMethod method;
    std::string uri;
    std::string version;
    HeaderMap headers;
    std::string body;

    static HttpRequest parse();
};

} // namespace http
