#pragma once

#include <string>
#include <vector>

/* GRAMMAR in EBNF
 * 	config_file = { server_block } ;
 *	server_block = "server" "{" { statement } "}" ;
 *	statement = directive | location_block ;
 *	directive = IDENTIFIER { parameter } ";" ;
 *	location_block = "location" IDENTIFIER "{" { directive } "}" ;
 *	parameter = IDENTIFIER | STRING | NUMBER ;
 */

typedef enum TokenType {
    IDENTIFIER,
    STRING,
    NUMBER,
    ENDPOINT,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    UNKNOWN
} TokenType;

typedef struct Token {
    std::string literal;
    TokenType type;
} Token;

class Lexer {
public:
    Lexer(std::string const &content, std::vector<Token> &res);
    void tokenize();
	void printTokens();

private:
    std::string const &content_;
    std::vector<Token> tokens_;
    size_t csize_;
    size_t pos_;
    size_t read_pos_;
    char ch_;

    void readChar();
    char peekChar();
    void eatWhitespaces();
    void pushToken(TokenType type, std::string const &literal);
    void pushToken(TokenType type, char);
    void pushToken(Token &);
    bool isFixedType();
    void parseWord();
    void pushFixedType();
};

class ParseConfig {
public:
    ParseConfig(int num_of_configs, char const **configs);
    ~ParseConfig();
};
