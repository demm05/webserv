#pragma once

#include <vector>
#include <string>
#include <map>

#include "LocationBlock.hpp"
#include "ConfigBuilder.hpp"

class ServerConfig {
public:
private:
    friend class ConfigBuilder;

    int port_;
    std::vector<std::string> serverNames_;
    std::map<std::string, LocationBlock> locations_;
};
