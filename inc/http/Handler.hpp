#pragma once

#include "config/LocationBlock.hpp"
#include "config/ServerBlock.hpp"
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
#include "RouterResult.hpp"

namespace http {

/**
 * @class IHandler
 * @brief Abstract interface for all request handlers (Strategy Pattern).
 *
 * Defines the contract for stateless handler objects that process HTTP requests.
 */
class IHandler {
public:
    virtual ~IHandler() {};
    /**
     * @brief The primary handler logic entry point.
     * @param request The client's HTTP request.
     * @param server The matched server configuration context.
     * @param location The matched location configuration context.
     * @return An HttpResponse object representing the result of the handling.
     */
    virtual HttpResponse handle(HttpRequest const &, config::ServerBlock const *,
                                config::LocationBlock const *) const = 0;

    /**
     * @brief Convenience overload to handle a request using a RouterResult.
     */
    HttpResponse handle(HttpRequest const &h, RouterResult const &r) const {
        return handle(h, r.server, r.location);
    }
};

/**
 * @brief Handles serving static files from the filesystem.
 */
class StaticFileHandler : public IHandler {
public:
    HttpResponse handle(HttpRequest const &, config::ServerBlock const *s = NULL,
                        config::LocationBlock const *l = NULL) const {
        (void)s;
        (void)l;
        return HttpResponse();
    }
};

/**
 * @brief Handles the generation of not found(404).
 */
class NotFoundHandler : public IHandler {
public:
    HttpResponse handle(HttpRequest const &, config::ServerBlock const *s = NULL,
                        config::LocationBlock const *l = NULL) const {
        (void)s;
        (void)l;
        return HttpResponse();
    }
};

/**
 * @brief Handles the execution of CGI scripts.
 */
class CGIHandler : public IHandler {
    HttpResponse handle(HttpRequest const &, config::ServerBlock const *s = NULL,
                        config::LocationBlock const *l = NULL) const {
        (void)s;
        (void)l;
        return HttpResponse();
    }
};

/**
 * @brief Handles the execution of CGI scripts.
 */
class ErrorHandler : public IHandler {
    HttpResponse handle(HttpRequest const &, config::ServerBlock const *s = NULL,
                        config::LocationBlock const *l = NULL) const {
        (void)s;
        (void)l;
        return HttpResponse();
    }
};

} // namespace http
