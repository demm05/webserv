#pragma once

#include "ConfigNode.hpp"
#include "Lexer.hpp"

/* GRAMMAR in EBNF
 * 	config_file = { server_block } ;
 *	server_block = "server" "{" { statement } "}" ;
 *	statement = directive | location_block ;
 *	directive = IDENTIFIER { parameter } ";" ;
 *	location_block = "location" IDENTIFIER "{" { directive } "}" ;
 *	parameter = IDENTIFIER | STRING | NUMBER ;
 */

class Parser {
private:
    std::string content_;
    ConfigNode nodes_;
    TokenArray tokens_;
    size_t pos_;

    Parser();
    Parser(char const *fpath);
    void parseIt();
    size_t size() const;

    Token const &currentToken() const;
    Token const &peekToken() const;
    void consumeToken();
    void expectToken(TokenType type);
    void expectToken(std::string literal);
    bool isTokenAValue() const;
    void displayCurrentToken() const;
    void addDirective(ConfigNode &node, DirectivePair const &pair) const;

    void handleServerBlock();
    void handleStatement();
    void handleLocationBlock();
    DirectivePair handleDirective();
};
