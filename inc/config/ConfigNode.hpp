#pragma once

#include <vector>
#include <map>
#include <string>
#include <utility>

class ConfigNode;

typedef std::vector<std::string> DirectiveArgs;
typedef std::map<std::string, DirectiveArgs> DirectiveMap;
typedef std::pair<std::string, DirectiveArgs> DirectivePair;
typedef std::vector<ConfigNode> ChildrenVec;

class ConfigNode {
public:
    ConfigNode() {
        args.reserve(3);
    };
    ConfigNode(std::string const &conf_name) : name(conf_name) {
        args.reserve(3);
    };
    std::string name;
    DirectiveArgs args;
    DirectiveMap directives;
    ChildrenVec children;
};
