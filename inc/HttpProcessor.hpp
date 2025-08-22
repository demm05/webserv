#pragma once
#include "HttpRequest.hpp"
// #include "HttpResponse.hpp"

class HttpProcessor {
public:
    HttpProcessor();
    ~HttpProcessor();

    // Process HTTP request and generate response
    // Input: raw request data, Output: HTTP response string
    std::string processRequest(const char *requestData, int length);

private:
    HttpRequest request_;
    //  HttpResponse response_;

    void handleGetRequest();
    void handlePostRequest();
    void serveStaticFile(const std::string &path);
};