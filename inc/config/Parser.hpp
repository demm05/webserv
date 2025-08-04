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
    Parser(char const &fpath);
    ~Parser();

private:
    ServerConfig config_;
    Lexer lexer_;
};
