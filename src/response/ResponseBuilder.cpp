#include "ResponseBuilder.hpp"
#include "ServerBlock.hpp"
#include "ServerConfig.hpp"
#include "HttpStatus.hpp"
#include <unistd.h>
#include <errno.h>
#include <iostream>

const char *defaultErrorFile = "errorpage.html";

bool ResponseBuilder::errorHandling(const std::string &httpVersion,
                                    const std::string &connectionType,
                                    const std::string &filePath) {

    if (errno == ENOENT) {
        return buildError(httpVersion, connectionType, http::NOT_FOUND, filePath);
    }
    if (errno == EACCES) {
        return buildError(httpVersion, connectionType, http::FORBIDDEN, filePath);
    }
    return buildError(httpVersion, connectionType, http::INTERNAL_SERVER_ERROR, filePath);
}

ResponseBuilder::ResponseBuilder() {
    serverBlockSet_ = false;
}

ResponseBuilder::ResponseBuilder(int port, const std::string &server_name,
                                 const config::ServerConfig &serverConfig) {
    if (!serverConfig.getServer(port, server_name, serverBlock_)) {
        serverBlockSet_ = false;
        return;
    }
    serverBlockSet_ = true;
}

bool ResponseBuilder::build(const std::string &httpVersion, const std::string &connectionType,
                            const std::string &method, const std::string &filePath,
                            const std::string &filename) {
    if (!serverBlockSet_) {
        std::cerr << "Server block not set. Cannot build response." << std::endl;
        return false;
    }
    if (method == "GET") {
        std::cout << "Building GET response for file: " << filePath << "/" << filename << std::endl;
        return buildGetFile(httpVersion, connectionType, filePath, filename);
    }
    std::cerr << "Unsupported method: " << method << std::endl;
    return false;
}

bool ResponseBuilder::buildGetFile(const std::string &httpVersion,
                                   const std::string &connectionType, const std::string &dirPath,
                                   const std::string &filename) {
    const config::LocationBlock *block = serverBlock_->getLocation("/" + filename);
    if (!block) {
        std::cerr << "No matching location block for path: " << "/" << filename << std::endl;
        return buildError(httpVersion, connectionType, http::NOT_FOUND, defaultErrorFile);
    }


        std::string fullPath = dirPath + "/" + filename;
    if (access(fullPath.c_str(), R_OK) == -1) {
        return errorHandling(httpVersion, connectionType, fullPath);
    }
    response_ = Response(httpVersion, connectionType,
                         http::StatusCode(http::OK),
                         ResponseContent(fullPath.c_str()));
    return true;
}

bool ResponseBuilder::buildError(const std::string &httpVersion, const std::string &connectionType,
                                 const http::Status &status, const std::string &filePath) {
    response_ = Response(httpVersion, connectionType, http::StatusCode(status), ResponseContent(filePath.c_str()));
    return true;
}

const Response &ResponseBuilder::getResponse() const {
    return response_;
}
