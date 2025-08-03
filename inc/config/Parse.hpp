#pragma once

/* GRAMMAR in EBNF
 * 	config_file = { server_block } ;
 *	server_block = "server" "{" { statement } "}" ;
 *	statement = directive | location_block ;
 *	directive = IDENTIFIER { parameter } ";" ;
 *	location_block = "location" IDENTIFIER "{" { directive } "}" ;
 *	parameter = IDENTIFIER | STRING | NUMBER ;
 */

class ParseConfig {
public:
    ParseConfig(int num_of_configs, char const **configs);
    ~ParseConfig();
};
