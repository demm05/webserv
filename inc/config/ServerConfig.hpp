#pragma once

#include "LocationBlock.hpp"
#include "DirectiveBlock.hpp"

class ServerConfig : public DirectiveBlock {
public:
    ServerConfig();
    void setPort(int port);
    void addServerName(std::string const &name);
    void addLocation(std::string const &path, LocationBlock const &location);

    int getPort() const;
    bool getLocation(std::string const &path, LocationBlock const **out_loc) const;
    LocationBlock const &getLocation(std::string const &path) const;

private:
    typedef std::map<std::string, LocationBlock> LocationMap;
    std::vector<std::string> names_;
    LocationMap locations_;
    int port_;
};