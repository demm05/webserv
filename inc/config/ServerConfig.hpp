#pragma once

#include "ServerBlock.hpp"

namespace config {

/**
 * @class ServerConfig
 * @brief A strongly-typed data container for a server block's configuration.
 *
 * This class holds the final, validated settings for a single 'server' block
 * after all parsing and semantic validation is complete. It is the definitive
 * configuration used by the webserver at runtime.
 */
class ServerConfig {
public:
    ServerConfig(char const *fpath);

    bool getServer(int port, std::string const &server_name, ServerBlock const *&res) const;
    ServerBlock const *getServer(int port, std::string const &server_name) const;

private:
    friend class ConfigBuilder;

    ServerBlockVec servers_; // TODO: Change CTL for performance
};

} // namespace config
