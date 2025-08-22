#include <iostream>
#include <exception>
#include "ServerConfig.hpp"
#include "ConfigException.hpp"

using config::ServerConfig;

int main(int argc, char const **argv) {
    if (argc < 2) {
        std::cerr << "Error: Config file should be provided" << std::endl;
        return 1;
    }
    try {
        ServerConfig cfg(argv[1]);
    } catch (config::ConfigException const &e) {
        std::cerr << e.what() << std::endl;
    } 
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    };
    return 0;
}
