#include "Response.hpp"

http::Response::Response()
    : httpVersion_("HTTP/1.1"), connectionType_("close"), statusCode_(http::OK), content_() {
    buildResponseStream();
}

http::Response::Response(const std::string &httpVersion, const std::string &connectionType,
                   const http::StatusCode &statusCode, const http::ResponseContent &content)
    : httpVersion_(httpVersion), connectionType_(connectionType), statusCode_(statusCode),
      content_(content) {
    buildResponseStream();
}

http::Response::Response(const http::Response &other)
    : httpVersion_(other.httpVersion_), connectionType_(other.connectionType_),
      statusCode_(other.statusCode_), content_(other.content_) {
    buildResponseStream();
}

http::Response &http::Response::operator=(const http::Response &other) {
    if (this != &other) {
        httpVersion_ = other.httpVersion_;
        connectionType_ = other.connectionType_;
        statusCode_ = other.statusCode_;
        content_ = other.content_;
        buildResponseStream();
    }
    return *this;
}

const std::string &http::Response::getHttpVersion() const {
    return httpVersion_;
}

const http::ResponseContent &http::Response::getContent() const {
    return content_;
}

const http::StatusCode &http::Response::getStatusCode() const {
    return statusCode_;
}

std::string http::Response::toString() const {
    return respStream_.str();
}

http::Response::~Response() {
}

void http::Response::buildResponseStream() {
    respStream_.str(""); // Clear the stream
    respStream_ << httpVersion_ << " " << statusCode_.getCode() << " " << statusCode_.getMessage()
                << "\r\n"
                << "Content-Type: " << content_.getType() << "\r\n"
                << "Content-Length: " << content_.getContentLength() << "\r\n"
                << "Connection: " << connectionType_ << "\r\n"
                << "\r\n"
                << content_.getBody();
}
