#pragma once

#include <vector>
#include <string>
#include <map>

#include "LocationBlock.hpp"

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
private:
    friend class ConfigBuilder;

    int port_;
    std::vector<std::string> serverNames_;
    std::map<std::string, LocationBlock> locations_;
};

typedef std::vector<ServerConfig> ServerConfigVec;

} // namespace config
