#pragma once

#include "Lexer.hpp"
#include "ServerConfig.hpp"

/* GRAMMAR in EBNF
 * 	config_file = { server_block } ;
 *	server_block = "server" "{" { statement } "}" ;
 *	statement = directive | location_block ;
 *	directive = IDENTIFIER { parameter } ";" ;
 *	location_block = "location" IDENTIFIER "{" { directive } "}" ;
 *	parameter = IDENTIFIER | STRING | NUMBER ;
 */

class Parser {
public:
    static ServerConfig parseFile(char const *fpath);

private:
    std::string content_;
    ServerConfig config_;
    Lexer::TokenArray tokens_;
    size_t pos_;

    Parser(char const *fpath);
    void run();
    size_t size();

    Token const &currentToken();
    Token const &peekToken();
    void consumeToken();
    void expectToken(TokenType type);
    void expectToken(std::string literal);

    void handleServerBlock();
    void handleStatement();
    void handleDirective();
    void handleLocationBlock();
};
