#include <iostream>
#include <exception>
#include "ConfigFileLoader.hpp"

using config::ConfigFileLoader;

void parsee(int num_of_configs, char const **configs) {
    (void)configs;
    for (int i = 0; i < num_of_configs; i++) {
        try {
            ConfigFileLoader::load(configs[i]);
        } catch (std::exception const &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        };
    }
}

int main(int argc, char const **argv) {
    if (argc < 2) {
        std::cerr << "Error: Config file should be provided" << std::endl;
        return 1;
    }
    parsee(argc - 1, argv + 1);
    return 0;
}
