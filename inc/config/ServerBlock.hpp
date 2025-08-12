#pragma once

#include <vector>
#include <string>
#include <map>

#include "LocationBlock.hpp"

namespace config {

class ServerBlock {
public:
    ServerBlock() : port_(-1) {
    }
    bool getLocation(std::string const &name, LocationBlock const *&res) const;
    LocationBlock const *getLocation(std::string const &name) const;
    bool matchServerName(std::string const &) const;

private:
    friend class ConfigBuilder;
    friend class ServerConfig;

    int port_;
    std::vector<std::string> serverNames_; // TODO: Change CTL for performance
    std::map<std::string, LocationBlock> locations_;
};

typedef std::vector<ServerBlock> ServerBlockVec;

} // namespace config
