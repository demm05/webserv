#pragma once

#include <string>
#include <sstream>
#include "HttpStatus.hpp"
#include "ResponseContent.hpp"

/**
 * @class Response
 * @brief Represents a complete HTTP response message.
 *
 * The Response class encapsulates the HTTP version string,
 * a status code (with its numeric code and reason phrase),
 * and the response content (body + MIME type).
 */
class Response {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty response with default members.
     */
    Response();

    /**
     * @brief Constructs a response with specified version, status, and content.
     *
     * @param httpVersion The HTTP version string (e.g., "HTTP/1.1").
     * @param statusCode  The HTTP status code and reason phrase wrapper.
     * @param content     The response body and MIME type.
     * @param connectionType The connection type (e.g., "close").
     */
    Response(const std::string &httpVersion, const std::string &connectionType,
             const http::StatusCode &statusCode, const ResponseContent &content);

    /**
     * @brief Copy constructor.
     *
     * Creates a new Response object as a copy of another.
     *
     * @param other The response to copy from.
     */
    Response(const Response &other);

    /**
     * @brief Copy assignment operator.
     *
     * Replaces the contents of this Response with another.
     *
     * @param other The response to copy from.
     * @return Reference to this instance.
     */
    Response &operator=(const Response &other);

    /**
     * @brief Gets the HTTP version string of the response.
     *
     * @return Constant reference to the version string.
     */
    const std::string &getHttpVersion() const;

    /**
     * @brief Gets the response content (body + MIME type).
     *
     * @return Constant reference to the ResponseContent object.
     */
    const ResponseContent &getContent() const;

    /**
     * @brief Gets the HTTP status code and reason phrase.
     *
     * @return Constant reference to the http::StatusCode object.
     */
    const http::StatusCode &getStatusCode() const;

    /**
     * @brief Converts the response to a string representation.
     *
     * Builds the full HTTP response string including headers and body.
     *
     * @return The complete HTTP response as a string.
     */
    std::string toString() const;

    /**
     * @brief Destructor.
     */
    ~Response();

private:
    std::string httpVersion_;       /**< HTTP version string, e.g. "HTTP/1.1". */
    std::string connectionType_;    /**< Connection type, e.g. "close". */
    http::StatusCode statusCode_;   /**< HTTP status code and reason phrase. */
    ResponseContent content_;       /**< Response body and its MIME type. */
    std::ostringstream respStream_; /**< Stream for building the response string. */

    void buildResponseStream();
};
