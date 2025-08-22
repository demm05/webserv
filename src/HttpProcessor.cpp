#include "HttpProcessor.hpp"
#include <iostream>
#include <fstream>

HttpProcessor::HttpProcessor() {
}

HttpProcessor::~HttpProcessor() {
}

std::string HttpProcessor::processRequest(const char *requestData, int length) {
    // Parse the HTTP request
    if (!request_.parseRequest(requestData, length)) {
        std::cerr << "Failed to parse HTTP request" << std::endl;
        // response_.buildServerError();
        // return response_.buildResponse();
    }

    // Route based on method
    if (request_.getMethod() == "GET") {
        handleGetRequest();
    } else if (request_.getMethod() == "POST") {
        handlePostRequest();
    } else {
        // Method not allowed
        // response_.setStatus(405, "Method Not Allowed");
        // response_.setContentType("text/html");
        // response_.setBody("<html><body><h1>405 Method Not Allowed</h1></body></html>");
    }

    //"could be stuff like this
    return response_.buildResponse();
}

// void HttpProcessor::handleGetRequest() {
//     std::string path = request_.getPath();

//     if (path == "/" || path == "/index.html") {
//         // Serve homepage (same as your C code)
//         response_.buildOk("<html>"
//                           "<head><title>Reactor HTTP Server</title></head>"
//                           "<body>"
//                           "<h1>Welcome to Reactor Server!</h1>"
//                           "<p>This server uses the Reactor design pattern.</p>"
//                           "<p>Request path: " +
//                               path +
//                               "</p>"
//                               "</body>"
//                               "</html>",
//                           "text/html");
//     } else if (path == "/hello") {
//         response_.buildOk("<html><body><h1>Hello World!</h1></body></html>", "text/html");
//     } else if (path == "/api/status") {
//         response_.buildOk("{\"status\": \"running\", \"server\": \"ReactorServer\"}",
//                           "application/json");
//     } else {
//         // Try to serve static file
//         serveStaticFile(path);
//     }
// }

// void HttpProcessor::handlePostRequest() {
//     // Simple POST handling
//     response_.buildOk("<html><body><h1>POST Request Received</h1><p>Data processing not "
//                       "implemented yet.</p></body></html>",
//                       "text/html");
// }

// void HttpProcessor::serveStaticFile(const std::string &path) {
//     // For now, just return 404 for any file requests
//     // You can implement file serving later
//     response_.buildNotFound();
// }