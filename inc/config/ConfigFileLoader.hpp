#pragma once

#include "ServerConfig.hpp"
#include <vector>

namespace config {

/**
 * @class ConfigFileLoader
 * @brief A facade that simplifies the configuration loading process.
 *
 * This class provides a single static method to handle the entire process
 * of reading a file, tokenizing, parsing, and building the final
 * configuration objects. It orchestrates the Lexer, Parser, and ConfigBuilder.
 */
class ConfigFileLoader {
public:
    /**
     * @brief Loads, parses, and builds server configurations from a file path.
     * @param fpath The path to the configuration file.
     * @return A vector of validated ServerConfig objects.
     * @throw std::exception on file, syntax, or semantic errors.
     */
    static std::vector<ServerConfig> load(const char *fpath);
};

} // namespace config
