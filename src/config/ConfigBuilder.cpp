#include <stdexcept>
#include <iostream>
#include "ConfigException.hpp"
#include "ConfigBuilder.hpp"

namespace config {

ConfigBuilder::ServerHandlerMap const &ConfigBuilder::getServerDirectiveHandlers() {
    static ServerHandlerMap map;
    if (!map.empty())
        return map;
    map["listen"] = &ConfigBuilder::handleListen;
    map["server_name"] = &ConfigBuilder::handleServerName;
    return map;
}

ConfigBuilder::LocationHandlerMap const &ConfigBuilder::getLocationDirectiveHandlers() {
    static LocationHandlerMap map;
    if (!map.empty())
        return map;
    map["root"] = &ConfigBuilder::handleRoot;
    map["index"] = &ConfigBuilder::handleIndex;
    return map;
}

ServerConfigVec ConfigBuilder::build(ConfigNodeVec const &nodes) {
    if (nodes.empty())
        throw ConfigError("config file is empty");
    ServerConfigVec v;
    v.reserve(nodes.size());
    ConfigBuilder cf;
    for (size_t i = 0; i < nodes.size(); i++) {
        v.push_back(cf.buildServer(nodes[i]));
    }
    return v;
}

ServerConfig ConfigBuilder::buildServer(ConfigNode const &node) {
    if (node.name != "server")
        throw std::runtime_error("ConfigBuilder unexpected call of buildServer non matching name");
    ServerConfig cf;
    buildServerDirectives(cf, node.directives);
    buildServerChildren(cf, node.children);
    return cf;
}

void ConfigBuilder::buildServerDirectives(ServerConfig &conf, DirectiveMap const &directives) {
    ServerHandlerMap handlers = getServerDirectiveHandlers();
    for (DirectiveMap::const_iterator it = directives.begin(); it != directives.end(); ++it) {
        ServerHandlerMap::const_iterator handler;
        std::string const &name = it->first;
        handler = handlers.find(name);
        if (handler == handlers.end())
            throw ConfigError("unknown directive '" + name + "' in server block");
        (this->*handler->second)(conf, it->second);
    }
}

void ConfigBuilder::buildServerChildren(ServerConfig &conf, ConfigNodeVec const &nodes) {
    typedef void (ConfigBuilder::*NodeHandler)(ServerConfig &, ConfigNode const &);
    typedef std::map<std::string, NodeHandler> NodeHandlerMap;

    NodeHandlerMap handlers;
    handlers["location"] = &ConfigBuilder::buildLocation;

    for (ConfigNodeVec::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
        NodeHandlerMap::const_iterator handler = handlers.find(it->name);
        if (handler == handlers.end()) {
            throw ConfigError("unknown block '" + it->name + "' in server block'");
        }
        (this->*handler->second)(conf, *it);
    }
}

void ConfigBuilder::buildLocation(ServerConfig &conf, ConfigNode const &node) {
    if (node.args.size() != 1) {
        throw ConfigError("location block requires exactly 1 path argument");
    }
    LocationBlock loc;
    loc.path = node.args[0];
    if (conf.locations_.count(loc.path) > 0) {
        issue_warning("Duplicate location '" + loc.path + "' in server block.");
        return;
    }

    LocationHandlerMap handlers = getLocationDirectiveHandlers();
    DirectiveMap const &directives = node.directives;
    for (DirectiveMap::const_iterator it = directives.begin(); it != directives.end(); ++it) {
        LocationHandlerMap::const_iterator handler;
        handler = handlers.find(it->first);
        if (handler == handlers.end()) {
            throw ConfigError("unknown directive '" + it->first + "' in server block");
        }
        (this->*handler->second)(loc, it->second);
    }
    conf.locations_[loc.path] = loc;
}

void ConfigBuilder::handleListen(ServerConfig &cfg, DirectiveArgs const &) {
    std::cout << "Listen caller" << std::endl;
    cfg.port_ = 80;
}

void ConfigBuilder::handleServerName(ServerConfig &, DirectiveArgs const &) {
    std::cout << "ServerName caller" << std::endl;
}

void ConfigBuilder::handleRoot(LocationBlock &, DirectiveArgs const &) {
    std::cout << "handleRoot caller" << std::endl;
}

void ConfigBuilder::handleIndex(LocationBlock &, DirectiveArgs const &) {
    std::cout << "handleIndex caller" << std::endl;
}

} // namespace config
