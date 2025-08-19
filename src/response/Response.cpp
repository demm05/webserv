#include "Response.hpp"

Response::Response()
    : httpVersion_("HTTP/1.1"), connectionType_("close"), statusCode_(http::OK), content_() {
    buildResponseStream();
}

Response::Response(const std::string &httpVersion, const std::string &connectionType,
                   const http::StatusCode &statusCode, const ResponseContent &content)
    : httpVersion_(httpVersion), connectionType_(connectionType), statusCode_(statusCode),
      content_(content) {
    buildResponseStream();
}

Response::Response(const Response &other)
    : httpVersion_(other.httpVersion_), connectionType_(other.connectionType_),
      statusCode_(other.statusCode_), content_(other.content_) {
    buildResponseStream();
}

Response &Response::operator=(const Response &other) {
    if (this != &other) {
        httpVersion_ = other.httpVersion_;
        connectionType_ = other.connectionType_;
        statusCode_ = other.statusCode_;
        content_ = other.content_;
        buildResponseStream();
    }
    return *this;
}

const std::string &Response::getHttpVersion() const {
    return httpVersion_;
}

const ResponseContent &Response::getContent() const {
    return content_;
}

const http::StatusCode &Response::getStatusCode() const {
    return statusCode_;
}

std::string Response::toString() const {
    return respStream_.str();
}

Response::~Response() {
}

void Response::buildResponseStream() {
    respStream_ << httpVersion_ << " " << statusCode_.getCode() << " " << statusCode_.getMessage()
                << "\r\n"
                << "Content-Type: " << content_.getType() << "\r\n"
                << "Content-Length: " << content_.getContentLength() << "\r\n"
                << "Connection: " << connectionType_ << "\r\n"
                << "\r\n"
                << content_.getBody();
}
