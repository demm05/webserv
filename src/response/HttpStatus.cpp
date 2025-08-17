#include "HttpStatus.hpp"

HttpStatus::StatusCode::StatusCode() : code_(HttpStatus::OK) {
}

HttpStatus::StatusCode::StatusCode(Status code) : code_(code) {
}

HttpStatus::StatusCode::StatusCode(const StatusCode &other) : code_(other.code_) {
}

HttpStatus::StatusCode &HttpStatus::StatusCode::operator=(const StatusCode &other) {
    if (this != &other) {
        code_ = other.code_;
    }
    return *this;
}

HttpStatus::Status HttpStatus::StatusCode::getCode() const {
    return code_;
}

const char *HttpStatus::StatusCode::getMessage() const {
    return statusMessage(code_);
}

HttpStatus::StatusCode::~StatusCode() {
}
