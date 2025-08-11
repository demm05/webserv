#include "ConfigBuilder.hpp"
#include <stdexcept>
#include <iostream>

namespace config {

ServerConfigVec ConfigBuilder::build(ConfigNodeVec const &nodes) {
    static ConfigBuilder cf;

    if (nodes.empty())
        throw std::runtime_error("config file is empty");

    ServerConfigVec v;
    v.reserve(nodes.size());
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
    typedef void (ConfigBuilder::*DirectiveHandler)(ServerConfig &, DirectiveArgs const &);
    typedef std::map<std::string, DirectiveHandler> DirectiveHandlerMap;

    DirectiveHandlerMap server_handlers;
    server_handlers["listen"] = &ConfigBuilder::handleListen;
    server_handlers["server_name"] = &ConfigBuilder::handleServerName;

    for (DirectiveMap::const_iterator it = directives.begin(); it != directives.end(); it++) {
        std::string const &name = it->first;

        DirectiveHandlerMap::const_iterator handler = server_handlers.find(name);
        if (handler == server_handlers.end())
            throw std::runtime_error("unknown directive '" + name + "' in server block");
        (this->*handler->second)(conf, it->second);
    }
}

void ConfigBuilder::buildServerChildren(ServerConfig &conf, ConfigNodeVec const &nodes) {
    typedef void (ConfigBuilder::*NodeHandler)(ServerConfig &, ConfigNode const &);
    typedef std::map<std::string, NodeHandler> NodeHandlerMap;

    NodeHandlerMap handlers;
    handlers["location"] = &ConfigBuilder::buildLocation;

    for (ConfigNodeVec::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
        NodeHandlerMap::const_iterator handler = handlers.find(it->name);
        if (handler == handlers.end()) {
            throw std::runtime_error("unknown block '" + it->name + "' in server block'");
        }
        (this->*handler->second)(conf, *it);
    }
}

void ConfigBuilder::buildLocation(ServerConfig &conf, ConfigNode const &node) {
    if (node.args.size() != 1) {
        throw std::runtime_error("location block requires exactly 1 path argument");
    }
    LocationBlock loc;
    loc.path = node.args[0];
    if (conf.locations_.count(loc.path) > 0) {
        std::cerr << "Warning: Duplicate location '" << loc.path
                  << "' in server block. Ignoring subsequent definition." << std::endl;
        return;
    }

    typedef void (ConfigBuilder::*DirectiveHandler)(LocationBlock &, DirectiveArgs const &);
    typedef std::map<std::string, DirectiveHandler> DirectiveHandlerMap;
    DirectiveHandlerMap handlers;
    handlers["root"] = &ConfigBuilder::handleRoot;
    handlers["index"] = &ConfigBuilder::handleIndex;

    DirectiveMap const &directives = node.directives;
    for (DirectiveMap::const_iterator it = directives.begin(); it != directives.end(); it++) {
        DirectiveHandlerMap::const_iterator handler = handlers.find(it->first);
        if (handler == handlers.end()) {
            throw std::runtime_error("unknown directive '" + it->first + "' in server block");
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
