#include <iostream>
#include <fstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include <exception>
#include <vector>
#include <cctype>
#include <sstream>

void parse_file(char const *fpath) {
    std::ifstream infile(fpath);
    if (!infile.is_open())
        throw std::runtime_error("`" + std::string(fpath) + "`: cannot be opened");
    std::stringstream buffer;
    buffer << infile.rdbuf();
    std::string fcontent = buffer.str();
    infile.close();
    std::vector<Token> res;
    res.reserve(100);
    Lexer l(fcontent, res);
    l.tokenize();
    l.printTokens();
}

void parsee(int num_of_configs, char const **configs) {
    for (int i = 0; i < num_of_configs; i++) {
        try {
            parse_file(configs[i]);
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
