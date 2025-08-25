#pragma once

#include <string>
#include "HttpStatus.hpp"
#include "Response.hpp"
#include "ServerConfig.hpp"

/**
 * @class ResponseBuilder
 * @brief Utility class for constructing and sending HTTP response messages.
 *
 * The ResponseBuilder provides high-level methods to build responses for
 * different scenarios (serving files, handling errors, redirects, etc.)
 * and helper methods for serializing and sending the response over a socket.
 */
class ResponseBuilder {
public:
    /**
     * @brief Constructor with port and server name.
     *
     * Initializes the ResponseBuilder with a specific port and server name.
     * This constructor is useful for building responses based on server configuration.
     *
     * @param port The port number to use for the response.
     * @param server_name The server name to use for the response.
     * @param serverConfig The server configuration reference to use for matching server blocks.
     *
     * @note This constructor does not build a response; it only initializes the internal state.
     *       Use the `build` method to create a response based on the server configuration.
     */
    ResponseBuilder(int port, const std::string &server_name,
                    const config::ServerConfig &serverConfig);

    /**
     * @brief Builds a response based on request information and server configuration.
     *
     * @param httpVersion    HTTP version string (e.g., "HTTP/1.1").
     * @param connectionType Connection type (e.g., "close" or "keep-alive").
     * @param method         HTTP request method (e.g., "GET", "HEAD").
     * @param dirPath       Path to the requested resource directory.
     * @param filename       Filename for the requested resource.
     * @return True if response was successfully built, false otherwise.
     */
    bool build(const std::string &httpVersion, const std::string &connectionType,
               const std::string &method, const std::string &dirPath, const std::string &filename);

    /**
     * @brief Builds a GET response for serving a file.
     *
     * @param httpVersion    HTTP version string.
     * @param connectionType Connection type string.
     * @param dirPath        Path to the file directory to serve metadata for.
     * @param filename       Filename for the requested resource.
     * @return True if the response was successfully built, false otherwise.
     */
    bool buildGetFile(const std::string &httpVersion, const std::string &connectionType,
                      const std::string &dirPath, const std::string &filename);

    // /**
    //  * @brief Builds a HEAD response (headers only, no body).
    //  *
    //  * @param httpVersion    HTTP version string.
    //  * @param connectionType Connection type string.
    //  * @param dirPath        Path to the file directory to serve metadata for.
    //  * @param filename       Filename for the requested resource.
    //  * @return True if the response was successfully built, false otherwise.
    //  */
    // bool buildHeadFile(const std::string &httpVersion, const std::string &connectionType,
    //                    const std::string &dirPath, const std::string &filename);

    /**
     * @brief Builds an error response.
     *
     * @param httpVersion    HTTP version string.
     * @param connectionType Connection type string.
     * @param status         HTTP status code object.
     * @param filePath       Path to a file for the error response body.
     * @return True if the response was successfully built, false otherwise.
     */
    bool buildError(const std::string &httpVersion, const std::string &connectionType,
                    const http::Status &status, const std::string &filePath);

    // /**
    //  * @brief Builds a redirect response.
    //  *
    //  * @param httpVersion    HTTP version string.
    //  * @param connectionType Connection type string.
    //  * @param location       Redirect target (Location header).
    //  * @param status         Redirect status code (e.g., 301, 302).
    //  * @return True if the response was successfully built, false otherwise.
    //  */
    // bool buildRedirect(const std::string &httpVersion, const std::string &connectionType,
    //                    const std::string &location, const http::StatusCode &status);

    /**
     * @brief Gets the internal Response object.
     *
     * @return Constant reference to the Response instance.
     */
    const http::Response &getResponse() const;

private:
    http::Response response_;                /**< The current response object. */
    const config::ServerBlock *serverBlock_; /**< Pointer to the server block configuration. */
    bool serverBlockSet_;                    /**< Flag indicating if the server block is set. */

    /**
     * @brief Default constructor.
     */
    ResponseBuilder();

    bool errorHandling(const std::string &httpVersion, const std::string &connectionType,
                       const std::string &filePath);
};
