#include "ServerConfig.hpp"

ServerConfig::ServerConfig() : port_(-1) {
    names_.reserve(5);
}
int ServerConfig::getPort() const {
    return port_;
}
void ServerConfig::setPort(int port) {
    if (port > 0 && port < 65536)
        port_ = port;
}
void ServerConfig::addServerName(std::string const &name) {
    names_.push_back(name);
}
void ServerConfig::addLocation(std::string const &path, LocationBlock const &location) {
    locations_[path] = location;
}
bool ServerConfig::getLocation(std::string const &path, LocationBlock const **out_loc) const {
    if (!out_loc)
        return false;
    LocationMap::const_iterator it = locations_.find(path);
    if (it != locations_.end()) {
        *out_loc = &(it->second);
        return true;
    }
    *out_loc = NULL;
    return false;
}

LocationBlock const &ServerConfig::getLocation(std::string const &path) const {
    return locations_.at(path);
}
