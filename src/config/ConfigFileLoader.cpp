#include <fstream>
#include <sstream>
#include <iostream>

#include "ConfigFileLoader.hpp"
#include "Lexer.hpp"
#include "ConfigNode.hpp"
#include "Parser.hpp"
#include "ConfigNode.hpp"
#include "ConfigBuilder.hpp"

using namespace config;

std::vector<ServerConfig> ConfigFileLoader::load(char const *fpath) {
    std::ifstream file(fpath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open config file.");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    TokenArray tokens = Lexer::tokenize(content);
    std::vector<ConfigNode> ir = Parser::parse(tokens);
    std::vector<ServerConfig> configs = ConfigBuilder::build(ir);
    return configs;
}
