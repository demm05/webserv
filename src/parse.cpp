#include <iostream>
#include <fstream>
#include "Parse.hpp"
#include <exception>
#include <vector>
#include <cctype>
#include <sstream>

// static inline void append_token(TokenType type, std::string const &literal,
//                                 std::vector<Token> &res) {
//     Token tok;
//     tok.literal = literal;
//     tok.type = type;
//     res.push_back(tok);
// }
//
// static inline bool is_string(int c) {
//     return (std::isalnum(c) && c == '_') ? 1 : 0;
// }
//
// void parse_line(std::string const &line, std::vector<Token> &res) {
//     size_t i = 0;
//     std::string literal;
//     while (i < line.size()) {
//         while (i < line.size() && std::isspace(line[i]))
//             i++;
//         if (line[i] == '#')
//             return;
//         else if (line[i] == '{')
//             append_token(LEFT_BRACE, &line[i++], res);
//         else if (line[i] == '}')
//             append_token(RIGHT_BRACE, &line[i++], res);
//         else if (line[i] == ';')
//             append_token(SEMICOLON, &line[i++], res);
//         else if (is_string(line[i])) {
//             literal.clear();
//             while (is_string(line[i])) {
//                 literal.append(&line[i++]);
//             }
//         }
//     }
// }

// void parse_file(char const *fpath) {
//     std::ifstream infile;
//     infile.open(fpath);
//     if (!infile.is_open())
//         throw std::runtime_error("`" + std::string(fpath) + "`: cannot be opened");
//     std::vector<Token> res(100);
//     std::string line;
//     line.reserve(100);
//     while (std::getline(infile, line)) {
//         parse_line(line, res);
//         line.clear();
//     }
// }

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
