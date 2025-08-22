

// serve as a proposal

/*
#pragma once

class HttpResponse {
public:
    HttpResponse();
    ~HttpResponse();

    // TODO: Implement these methods to build HTTP responses
    void setStatus(int code, const std::string& reason = "");
    void setHeader(const std::string& name, const std::string& value);
    void setBody(const std::string& body);
    void setContentType(const std::string& contentType);

    // TODO: This should return a complete HTTP response string
    // Format: "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html>...</html>"
    std::string buildResponse() const;

    // TODO: Quick response builders - implement these for common responses
    void buildNotFound();        // Should generate 404 response
    void buildServerError();     // Should generate 500 response
    void buildOk(const std::string& content, const std::string& contentType = "text/html");

private:
    // TODO: Store response data here
    int statusCode_;
    std::string reasonPhrase_;
    std::map<std::string, std::string> headers_;
    std::string body_;

    // TODO: Helper to get standard reason phrases
    std::string getDefaultReasonPhrase(int code) const;
};

*/